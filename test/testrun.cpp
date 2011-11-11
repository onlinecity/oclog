#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "LogTest.h"
#include "ThreadTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(LogTest);
CPPUNIT_TEST_SUITE_REGISTRATION(ThreadTest);

int main(int argc, char **argv)
{
	CppUnit::TextUi::TestRunner runner;
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
	runner.addTest(registry.makeTest());
	return runner.run() ? 0 : 1;
}
