/*
 * Copyright (C) 2011 OnlineCity
 * Licensed under the MIT license, which can be read at: http://www.opensource.org/licenses/mit-license.php
 * @author hd@onlinecity.dk & td@onlinecity.dk
 */

#ifndef SINK_H_
#define SINK_H_

#include <iostream>
#include <sstream>
#include <iomanip>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include "LogLevel.h"

namespace oc {
namespace log {

/**
 * polymorphic base class for sinks.
 * Contains common formatting functions.
 */
class Sink
{
public:

	virtual void stream(const std::string &category, const int &logLevel, std::ostringstream& os) = 0;

	virtual ~Sink()
	{

	}

	std::string getLevelString(const int &logLevel);

	/**
	 * Returns a timestring with the following format in GMT:
	 * "2011-11-11T13:45:21.53"
	 * @return
	 */
	std::string getTimeString();

};

} // log
} // oc

#endif /* SINK_H_ */
