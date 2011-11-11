#ifndef LOGTEST_H_
#define LOGTEST_H_

#include <iostream>
#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Log.h"
#include "Sink.h"
#include "FileSink.h"
#include "CerrSink.h"
#include "macros.h"
#include "ScribeSink.h"

using namespace std;
using namespace oc::log;

class LogTest: public CppUnit::TestFixture
{

public:

	void setUp()
	{

	}

	void tearDown()
	{

	}

	void testLog()
	{
//		OCLOG(DEBUG) << "Hello world";
//		oc::log::Log<oc::log::CerrSink>("test1").get() << "Hello world";

		Log<CerrSink>::getLevel() = DEBUG;
		OC_LOG(CerrSink,"test1",DEBUG) << "Hello world 2";
		OC_LOG(CerrSink,"test1",ALERT) << "Hello world 3";
	}

	void testFileLog()
	{

		OC_LOG(FileSink,"test2",DEBUG) << "Hello world 4";
		Log<FileSink>("test2","other.log").get() << "Hello World 5";
		Log<FileSink>("test2").get() << "Hello World 6";
		OC_LOG(FileSink,"test2",DEBUG) << "Hello world 7";
		OC_LOG(FileSink,"test2",DEBUG) << "Hello world 8";
		OC_LOG(FileSink,"test2",DEBUG) << "Hello world 9";
		Log<FileSink>::getLevel() = ERROR;
		OC_LOG(FileSink,"test2",DEBUG) << "Hello world 10";
		OC_LOG(FileSink,"test2",DEBUG) << "Hello world 11";
		OC_LOG(FileSink,"test2",DEBUG) << "Hello world 12";
	}

	void testScribeLog()
	{
		Log<ScribeSink>("test3").get() << "Hello World";
	}

	CPPUNIT_TEST_SUITE(LogTest);
	CPPUNIT_TEST(testLog);
	CPPUNIT_TEST(testFileLog);
	CPPUNIT_TEST(testScribeLog);
	CPPUNIT_TEST_SUITE_END();

};


#endif /* LOGTEST_H_ */
