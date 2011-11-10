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

#include <map>
#include <boost/shared_ptr.hpp>

namespace oc {
namespace log {

enum TLogLevel
{
	EMERGENCY, CRITICAL, ALERT, ERROR, WARNING, NOTICE, INFO, DEBUG
};

template<class T>
class Log
{
typedef typename std::map<std::string, boost::shared_ptr<T> > SinkMap;
typedef typename SinkMap::const_iterator SinkIterator;
typedef typename std::pair<std::string, boost::shared_ptr<T> > SinkPair;

private:
	std::ostringstream os;
	std::string cat;
	boost::shared_ptr<T> sink;

public:

	Log(std::string category, std::string name = "", std::string port = "");

	~Log()
	{
		sink->stream(cat, os);
	}

	std::ostringstream& get()
	{
		return os;
	}

	static TLogLevel& getLevel()
	{
		static TLogLevel level = DEBUG;
		return level;
	}

private:

	static boost::shared_ptr<T> getSink(std::string name, std::string port);
};

template <class T>
boost::shared_ptr<T> Log<T>::getSink(std::string name, std::string port)
{
	static SinkMap sinks = SinkMap();
	SinkIterator it = sinks.find(name);
	if (sinks.empty() || it == sinks.end()) {
		sinks.insert(SinkPair(name, boost::shared_ptr<T>(new T(name, port))));
		it = sinks.find(name);
	}
	return (*it).second;
}

template<class T>
Log<T>::Log(std::string category, std::string name, std::string port) :
		cat(category), sink(Log<T>::getSink(name, port))
{
}

} // oc
} // log

#endif /* LOG_H_ */
