/*
 * Copyright (C) 2011 OnlineCity
 * Licensed under the MIT license, which can be read at: http://www.opensource.org/licenses/mit-license.php
 * @author hd@onlinecity.dk & td@onlinecity.dk
 */

#ifndef SINK_H_
#define SINK_H_

#include <iostream>
#include <sstream>

namespace oc {
namespace log {

class Sink
{
public:

	virtual void stream(std::string category, std::ostringstream& os) = 0;

	virtual ~Sink()
	{

	}


};


} // log
} // oc

#endif /* SINK_H_ */
