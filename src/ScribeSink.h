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

/**
 * ScribeSink logs its output to a scribe server.
 * It uses an FIFO queue and it flushes on every 10 entries or on dtor.
 * Uses mutex locking for thread synchronisation. Connects to 127.0.0.1:1463 if hostname and port is omitted.
 */
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

	ScribeSink(std::string hostname, std::string port);

	~ScribeSink();

	void stream(const std::string &category, const int &logLevel, std::ostringstream& os);
};

}
}

#endif /* SCRIBESINK_H_ */
