/*
 * Copyright (C) 2011 OnlineCity
 * Licensed under the MIT license, which can be read at: http://www.opensource.org/licenses/mit-license.php
 * @author hd@onlinecity.dk & td@onlinecity.dk
 */

#include "Sink.h"

namespace oc {
namespace log {

std::string Sink::getLevelString(const int &logLevel)
{
	switch (logLevel) {
		case LOG_EMERGENCY:
			return "EMERG";
		case LOG_CRITICAL:
			return "CRIT ";
		case LOG_ALERT:
			return "ALERT";
		case LOG_ERROR:
			return "ERROR";
		case LOG_WARNING:
			return "WARN ";
		case LOG_NOTICE:
			return "NOTE ";
		case LOG_INFO:
			return "INFO ";
		case LOG_DEBUG:
			return "DEBUG";
		default:
			return "DEBUG";
	}
}

std::string Sink::getTimeString()
{
	std::stringstream ss;
	boost::posix_time::ptime pt = boost::posix_time::microsec_clock::universal_time();
	boost::gregorian::date d = pt.date();
	boost::posix_time::time_duration td = pt.time_of_day();
	double fracsecs = (boost::numeric_cast<double, long>(td.fractional_seconds()) / 1000000) + td.seconds();
	ss << std::setfill('0') << std::setw(2) << d.year() << "-" << std::setfill('0') << std::setw(2)
			<< static_cast<int>(d.month()) << "-" << std::setfill('0') << std::setw(2) << d.day() << "T"
			<< std::setfill('0') << std::setw(2) << td.hours() << ":" << std::setfill('0') << std::setw(2)
			<< td.minutes() << ":" << std::setfill('0') << std::setw(5) << std::fixed << std::setprecision(2)
			<< fracsecs;
	return ss.str();
}

}
}
