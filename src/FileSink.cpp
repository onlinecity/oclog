/*
 * Copyright (C) 2011 OnlineCity
 * Licensed under the MIT license, which can be read at: http://www.opensource.org/licenses/mit-license.php
 * @author hd@onlinecity.dk & td@onlinecity.dk
 */

#include "FileSink.h"

namespace oc {
namespace log {

FileSink::FileSink(std::string filename, std::string port) :
		fs(new std::ofstream(filename != "" ? filename.c_str() : "debug.log", std::fstream::app | std::fstream::out))
{
}

/**
 * The deconstructor closes the file.
 */
FileSink::~FileSink()
{
	if (fs->is_open()) fs->close();
}

void FileSink::stream(const std::string &category, const int &logLevel, std::ostringstream& os)
{
	if (!fs->is_open()) throw std::runtime_error("FileStream closed");
	if (fs->fail()) throw std::runtime_error("FileStream failed");

	*fs << getTimeString() << " " << getLevelString(logLevel) << " " << category << ": " << os.str() << std::endl;

}

}
}
