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

class FileSink: public Sink
{
private:
	boost::shared_ptr<std::ofstream> fs;

public:

	FileSink(std::string filename, std::string port) :
			fs(new std::ofstream(filename != "" ? filename.c_str() : "debug.log", std::fstream::app | std::fstream::out))
	{

	}

	~FileSink()
	{
		if (fs->is_open()) fs->close();
	}

	void stream(std::string category, std::ostringstream& os)
	{
		if (!fs->is_open() || fs->fail()) throw std::runtime_error("FileStream failed");
		*fs << category << ": " << os.str() << std::endl;
	}
};

}
}

#endif /* FILESINK_H_ */
