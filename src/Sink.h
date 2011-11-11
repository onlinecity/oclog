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

namespace oc {
namespace log {

class Sink
{
public:

	virtual void stream(std::string category, std::ostringstream& os) = 0;

	virtual ~Sink()
	{

	}

	std::string getTimeString()
	{
		std::stringstream ss;
		boost::posix_time::ptime pt = boost::posix_time::microsec_clock::universal_time();
		boost::gregorian::date d = pt.date();
		boost::posix_time::time_duration td = pt.time_of_day();
		double fracsecs = (boost::numeric_cast<double,long>(td.fractional_seconds())/1000000)+td.seconds();
		ss 	<< std::setfill('0') << std::setw(2) << d.year() << "-"
			<< std::setfill('0') << std::setw(2) << static_cast<int>(d.month()) << "-"
			<< std::setfill('0') << std::setw(2) << d.day() << "T"
			<< std::setfill('0') << std::setw(2) << td.hours() << ":"
			<< std::setfill('0') << std::setw(2) << td.minutes() << ":"
			<< std::setfill('0') << std::setw(5) << std::fixed << std::setprecision(2) << fracsecs;
		return ss.str();
	}

};


} // log
} // oc

#endif /* SINK_H_ */
