/*
 * Copyright (C) 2011 OnlineCity
 * Licensed under the MIT license, which can be read at: http://www.opensource.org/licenses/mit-license.php
 * @author hd@onlinecity.dk & td@onlinecity.dk
 */

#include "ScribeSink.h"

namespace oc {
namespace log {

ScribeSink::ScribeSink(std::string hostname, std::string port) :
				socket(
						new TSocket(hostname != "" ? hostname : "127.0.0.1", port != "" ? boost::lexical_cast<int>(port) : 1463)),
				transport(new TFramedTransport(socket)),
				protocol(new TBinaryProtocol(transport)),
				client(new scribeClient(protocol))
{
	socket->open();
}

ScribeSink::~ScribeSink()
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

void ScribeSink::stream(const std::string &category, const int &logLevel, std::ostringstream& os)
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
	e.__set_message(getTimeString() + " " + getLevelString(logLevel) + " " +  os.str());
	entryQueue.push(e);
}

}
}
