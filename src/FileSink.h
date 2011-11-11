/*
 * Copyright (C) 2011 OnlineCity
 * Licensed under the MIT license, which can be read at: http://www.opensource.org/licenses/mit-license.php
 * @author hd@onlinecity.dk & td@onlinecity.dk
 */

#ifndef FILESINK_H_
#define FILESINK_H_

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <boost/shared_ptr.hpp>
#include "Sink.h"

namespace oc {
namespace log {

/**
 * The FileSink appends its output to a file. If a filename is omitted, the FileSink writes to the file "debug.log".
 */
class FileSink: public Sink
{
private:
	boost::shared_ptr<std::ofstream> fs;

public:

	FileSink(std::string filename, std::string port);

	/**
	 * The deconstructor closes the file.
	 */
	virtual ~FileSink();

	void stream(const std::string &category, const int &logLevel, std::ostringstream& os);

};

}
}

#endif /* FILESINK_H_ */
