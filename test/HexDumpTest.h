#ifndef HEXDUMPTEST_H_
#define HEXDUMPTEST_H_

#include <iostream>
#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>
#include <stdint.h>
#include "hexdump.h"

using namespace std;
using namespace oc::log;

class HexDumpTest: public CppUnit::TestFixture
{

public:

	void setUp()
	{

	}

	void tearDown()
	{

	}

	void test7()
	{
		uint8_t data[] = "hello world hello world hello world";
		string expected = "00000000  68 65 6c 6c 6f 20 77                              |hello w|\n"
				"00000007\n";
		CPPUNIT_ASSERT_EQUAL(expected, hexdump(data, 7));
	}

	void test8()
	{
		uint8_t data[] = "hello world hello world hello world";
		string expected = "00000000  68 65 6c 6c 6f 20 77 6f                           |hello wo|\n"
				"00000008\n";

		CPPUNIT_ASSERT_EQUAL(expected, hexdump(data, 8));
	}

	void test9()
	{
		uint8_t data[] = "hello world hello world hello world";
		string expected = "00000000  68 65 6c 6c 6f 20 77 6f  72                       |hello wor|\n"
				"00000009\n";

		CPPUNIT_ASSERT_EQUAL(expected, hexdump(data, 9));
	}

	void test16()
	{
		uint8_t data[] = "hello world hello world hello world";
		string expected = "00000000  68 65 6c 6c 6f 20 77 6f  72 6c 64 20 68 65 6c 6c  |hello world hell|\n"
				"00000010\n";
		CPPUNIT_ASSERT_EQUAL(expected, hexdump(data, 16));
	}

	void test17()
	{
		uint8_t data[] = "hello world hello world hello world";
		string expected = "00000000  68 65 6c 6c 6f 20 77 6f  72 6c 64 20 68 65 6c 6c  |hello world hell|\n"
				"00000010  6f                                                |o|\n"
				"00000011\n";
		CPPUNIT_ASSERT_EQUAL(expected, hexdump(data, 17));
	}

	void test25()
	{
		uint8_t data[] = "hello world hello world hello world";
		string expected = "00000000  68 65 6c 6c 6f 20 77 6f  72 6c 64 20 68 65 6c 6c  |hello world hell|\n"
				"00000010  6f 20 77 6f 72 6c 64 20  68                       |o world h|\n"
				"00000019\n";

		CPPUNIT_ASSERT_EQUAL(expected, hexdump(data, 25));
	}

	void testDump()
	{
		uint8_t data[] = "hello world hello world hello world";
		string expected = "00000000  68 65 6c 6c 6f 20 77 6f  72 6c 64 20 68 65 6c 6c  |hello world hell|\n"
				"00000010  6f 20 77 6f 72 6c 64 20  68 65 6c 6c 6f 20 77 6f  |o world hello wo|\n"
				"00000020  72 6c 64 00                                       |rld.|\n"
				"00000024\n";

		CPPUNIT_ASSERT_EQUAL(expected, hexdump(data, 0x24));
	}

CPPUNIT_TEST_SUITE(HexDumpTest);

		CPPUNIT_TEST(test7);
		CPPUNIT_TEST(test8);
		CPPUNIT_TEST(test9);
		CPPUNIT_TEST(test16);
		CPPUNIT_TEST(test17);
		CPPUNIT_TEST(test25);
		CPPUNIT_TEST(testDump);

	CPPUNIT_TEST_SUITE_END();

};

#endif /* LOGTEST_H_ */
