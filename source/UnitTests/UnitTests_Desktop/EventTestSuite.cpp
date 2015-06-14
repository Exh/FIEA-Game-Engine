/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>

bool suite_EventTestSuite_init = false;
#include "EventTestSuite.h"

static EventTestSuite suite_EventTestSuite;

static CxxTest::List Tests_EventTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_EventTestSuite( "C:/dev/students/ch11/srajanswain/Programming 2/FieaGameEngine/source/UnitTests/UnitTests_Desktop/EventTestSuite.h", 14, "EventTestSuite", suite_EventTestSuite, Tests_EventTestSuite );

static class TestDescription_suite_EventTestSuite_TestSubscription : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EventTestSuite_TestSubscription() : CxxTest::RealTestDescription( Tests_EventTestSuite, suiteDescription_EventTestSuite, 17, "TestSubscription" ) {}
 void runTest() { suite_EventTestSuite.TestSubscription(); }
} testDescription_suite_EventTestSuite_TestSubscription;

static class TestDescription_suite_EventTestSuite_TestQueueing : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EventTestSuite_TestQueueing() : CxxTest::RealTestDescription( Tests_EventTestSuite, suiteDescription_EventTestSuite, 48, "TestQueueing" ) {}
 void runTest() { suite_EventTestSuite.TestQueueing(); }
} testDescription_suite_EventTestSuite_TestQueueing;

static class TestDescription_suite_EventTestSuite_TestEventProperties : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EventTestSuite_TestEventProperties() : CxxTest::RealTestDescription( Tests_EventTestSuite, suiteDescription_EventTestSuite, 113, "TestEventProperties" ) {}
 void runTest() { suite_EventTestSuite.TestEventProperties(); }
} testDescription_suite_EventTestSuite_TestEventProperties;

