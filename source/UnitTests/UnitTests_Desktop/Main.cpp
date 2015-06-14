/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ParenPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ParenPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ParenPrinter >( tmp, argc, argv );
    return status;
}
bool suite_SampleTestSuite_init = false;
#include "Main.h"

static SampleTestSuite suite_SampleTestSuite;

static CxxTest::List Tests_SampleTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_SampleTestSuite( "C:/dev/students/ch11/srajanswain/Programming 2/FieaGameEngine/source/UnitTests/UnitTests_Desktop/Main.h", 8, "SampleTestSuite", suite_SampleTestSuite, Tests_SampleTestSuite );

static class TestDescription_suite_SampleTestSuite_TestAddition : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_SampleTestSuite_TestAddition() : CxxTest::RealTestDescription( Tests_SampleTestSuite, suiteDescription_SampleTestSuite, 11, "TestAddition" ) {}
 void runTest() { suite_SampleTestSuite.TestAddition(); }
} testDescription_suite_SampleTestSuite_TestAddition;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
