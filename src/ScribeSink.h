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
#include "scribe_types.h"
#include "scribe.h"
#include <vector>
#include "Sink.h"

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
	std::vector<LogEntry> entries;

public:

	ScribeSink(std::string hostname, std::string port) :
					socket(
							new TSocket(hostname != "" ? hostname : "127.0.0.1",
									port != "" ? boost::lexical_cast<int>(port) : 1463)),
					transport(new TFramedTransport(socket)),
					protocol(new TBinaryProtocol(transport)),
					client(new scribeClient(protocol))
	{
		socket->open();
	}

	~ScribeSink()
	{
		client->Log(entries);
	}

	void stream(std::string category, std::ostringstream& os)
	{
		os << std::flush;
		LogEntry e;
		e.__set_category(category);
		e.__set_message(os.str());
		entries.push_back(e);
	}
};

}
}

#endif /* SCRIBESINK_H_ */
