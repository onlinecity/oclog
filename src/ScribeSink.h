/*
 * Copyright (C) 2011 OnlineCity
 * Licensed under the MIT license, which can be read at: http://www.opensource.org/licenses/mit-license.php
 * @author hd@onlinecity.dk & td@onlinecity.dk
 */

#ifndef SCRIBESINK_H_
#define SCRIBESINK_H_

#include <transport/TSocket.h>
#include <transport/TTransport.h>
#include <transport/TBufferTransports.h>
#include <protocol/TBinaryProtocol.h>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread/mutex.hpp>
#include "scribe_types.h"
#include "scribe.h"
#include <vector>
#include "Sink.h"
#include "SinkQueue.h"

using namespace apache::thrift;
using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;
using namespace scribe::thrift;

namespace oc {
namespace log {

class ScribeSink: public Sink
{

private:
	boost::shared_ptr<TTransport> socket;
	boost::shared_ptr<TTransport> transport;
	boost::shared_ptr<TProtocol> protocol;
	boost::shared_ptr<scribeClient> client;
	boost::mutex mutex;
	SinkQueue<LogEntry> entryQueue;

public:

	ScribeSink(std::string hostname, std::string port) :
					socket(
							new TSocket(hostname != "" ? hostname : "127.0.0.1", port != "" ? boost::lexical_cast<int>(port) : 1463)),
					transport(new TFramedTransport(socket)),
					protocol(new TBinaryProtocol(transport)),
					client(new scribeClient(protocol))
	{
		socket->open();
	}

	~ScribeSink()
	{
		std::vector<LogEntry> entries;
		LogEntry log;

		while (!entryQueue.empty()) {
			entryQueue.wait_and_pop(log);
			entries.push_back(log);
		}

		boost::mutex::scoped_lock lock(mutex);
		client->Log(entries);
	}

	void stream(std::string category, std::ostringstream& os)
	{
		static int i = 0;
		if (++i % 10 == 0) {

			std::vector<LogEntry> entries;
			LogEntry log;

			while (!entryQueue.empty() && entryQueue.try_pop(log)) {
				entries.push_back(log);
			}
			boost::mutex::scoped_lock lock(mutex);
			client->Log(entries);
		}
		os << std::flush;
		LogEntry e;
		e.__set_category(category);
		e.__set_message(getTimeString() + " " + os.str());
		entryQueue.push(e);
	}
};

}
}

#endif /* SCRIBESINK_H_ */
