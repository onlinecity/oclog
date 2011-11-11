/*
 * Copyright (C) 2011 OnlineCity
 * Licensed under the MIT license, which can be read at: http://www.opensource.org/licenses/mit-license.php
 * @author hd@onlinecity.dk & td@onlinecity.dk
 */

#ifndef LOG_H_
#define LOG_H_

#include <iostream>
#include <string>
#include <sstream>
#include "Sink.h"
#include "CerrSink.h"
#include "FileSink.h"
#include "ScribeSink.h"
#include "LogLevel.h"

#include <map>
#include <boost/shared_ptr.hpp>


namespace oc {
namespace log {

/**
 * Basic logging system, that write its output to "Sinks".
 * Templated to support different sink classes. You can use one of the following sinks:
 *  CerrSink, FileSink, ScribeSink.
 *
 * Sinks are stored in a static map after they are initialized. Output is written the to sink
 * during destruction of the Log object.
 */
template<class T>
class Log
{
	typedef typename std::map<std::string, boost::shared_ptr<T> > SinkMap;
	typedef typename SinkMap::const_iterator SinkIterator;
	typedef typename std::pair<std::string, boost::shared_ptr<T> > SinkPair;

private:
	std::ostringstream os;
	std::string cat;
	TLogLevel level;
	boost::shared_ptr<T> sink;

public:
	Log(std::string category, TLogLevel logLevel, std::string name = "", std::string port = "");

	~Log()
	{
		sink->stream(cat, level, os);
	}

	std::ostringstream& get()
	{
		return os;
	}

	/**
	 * @return reference to the log level.
	 */
	static TLogLevel& getLevel()
	{
		static TLogLevel level = LOG_DEBUG;
		return level;
	}

private:
	/**
	 * Returns a shared_ptr to the sink specified by name and port.
	 * @param name
	 * @param port
	 * @return
	 */
	static boost::shared_ptr<T> getSink(std::string name, std::string port);
};

template<class T>
boost::shared_ptr<T> Log<T>::getSink(std::string name, std::string port)
{
	static SinkMap sinks = SinkMap();
	SinkIterator it = sinks.find(name + port);
	if (sinks.empty() || it == sinks.end()) {
		sinks.insert(SinkPair(name + port, boost::shared_ptr<T>(new T(name, port))));
		it = sinks.find(name + port);
	}
	return (*it).second;
}

template<class T>
Log<T>::Log(std::string category, TLogLevel logLevel, std::string name, std::string port) :
		cat(category), level(logLevel), sink(Log<T>::getSink(name, port))
{
}

} // oc
} // log

#endif /* LOG_H_ */
