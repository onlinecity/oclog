/*
 * Copyright (C) 2011 OnlineCity
 * Licensed under the MIT license, which can be read at: http://www.opensource.org/licenses/mit-license.php
 * @author hd@onlinecity.dk & td@onlinecity.dk
 */

#ifndef CERRSINK_H_
#define CERRSINK_H_

#include <iostream>
#include <sstream>
#include "Sink.h"

namespace oc {
namespace log {

class CerrSink: public Sink
{
public:

	CerrSink(std::string name="", std::string port="")
	{

	}

	void stream(std::string category, std::ostringstream& os)
	{
		std::cerr << getTimeString() << " " << category << ": " << os.str() << std::endl;
	}

	~CerrSink()
	{

	}
};

} // log
} // oc


#endif /* CERRSINK_H_ */
