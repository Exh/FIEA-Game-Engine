/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>

bool suite_AsyncEventTestSuite_init = false;
#include "AsyncEventTestSuite.h"

static AsyncEventTestSuite suite_AsyncEventTestSuite;

static CxxTest::List Tests_AsyncEventTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_AsyncEventTestSuite( "C:/dev/students/ch11/srajanswain/Programming 2/FieaGameEngine/source/UnitTests/UnitTests_Desktop/AsyncEventTestSuite.h", 19, "AsyncEventTestSuite", suite_AsyncEventTestSuite, Tests_AsyncEventTestSuite );

static class TestDescription_suite_AsyncEventTestSuite_TestStress : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AsyncEventTestSuite_TestStress() : CxxTest::RealTestDescription( Tests_AsyncEventTestSuite, suiteDescription_AsyncEventTestSuite, 22, "TestStress" ) {}
 void runTest() { suite_AsyncEventTestSuite.TestStress(); }
} testDescription_suite_AsyncEventTestSuite_TestStress;

static class TestDescription_suite_AsyncEventTestSuite_TestSubscribe : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AsyncEventTestSuite_TestSubscribe() : CxxTest::RealTestDescription( Tests_AsyncEventTestSuite, suiteDescription_AsyncEventTestSuite, 58, "TestSubscribe" ) {}
 void runTest() { suite_AsyncEventTestSuite.TestSubscribe(); }
} testDescription_suite_AsyncEventTestSuite_TestSubscribe;

static class TestDescription_suite_AsyncEventTestSuite_TestUnsubscribe : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AsyncEventTestSuite_TestUnsubscribe() : CxxTest::RealTestDescription( Tests_AsyncEventTestSuite, suiteDescription_AsyncEventTestSuite, 99, "TestUnsubscribe" ) {}
 void runTest() { suite_AsyncEventTestSuite.TestUnsubscribe(); }
} testDescription_suite_AsyncEventTestSuite_TestUnsubscribe;

static class TestDescription_suite_AsyncEventTestSuite_TestEnqueueMore_Action : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AsyncEventTestSuite_TestEnqueueMore_Action() : CxxTest::RealTestDescription( Tests_AsyncEventTestSuite, suiteDescription_AsyncEventTestSuite, 140, "TestEnqueueMore_Action" ) {}
 void runTest() { suite_AsyncEventTestSuite.TestEnqueueMore_Action(); }
} testDescription_suite_AsyncEventTestSuite_TestEnqueueMore_Action;

static class TestDescription_suite_AsyncEventTestSuite_TestEnqueueMore_Reaction : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AsyncEventTestSuite_TestEnqueueMore_Reaction() : CxxTest::RealTestDescription( Tests_AsyncEventTestSuite, suiteDescription_AsyncEventTestSuite, 182, "TestEnqueueMore_Reaction" ) {}
 void runTest() { suite_AsyncEventTestSuite.TestEnqueueMore_Reaction(); }
} testDescription_suite_AsyncEventTestSuite_TestEnqueueMore_Reaction;

