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

bool suite_StackTestSuite_init = false;
#include "StackTest.h"

static StackTestSuite suite_StackTestSuite;

static CxxTest::List Tests_StackTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_StackTestSuite( "C:/dev/students/ch11/srajanswain/Programming 2/FieaGameEngine/source/UnitTests/UnitTests_Desktop/StackTest.h", 12, "StackTestSuite", suite_StackTestSuite, Tests_StackTestSuite );

static class TestDescription_suite_StackTestSuite_TestPushAndTop : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_StackTestSuite_TestPushAndTop() : CxxTest::RealTestDescription( Tests_StackTestSuite, suiteDescription_StackTestSuite, 37, "TestPushAndTop" ) {}
 void runTest() { suite_StackTestSuite.TestPushAndTop(); }
} testDescription_suite_StackTestSuite_TestPushAndTop;

static class TestDescription_suite_StackTestSuite_TestPop : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_StackTestSuite_TestPop() : CxxTest::RealTestDescription( Tests_StackTestSuite, suiteDescription_StackTestSuite, 66, "TestPop" ) {}
 void runTest() { suite_StackTestSuite.TestPop(); }
} testDescription_suite_StackTestSuite_TestPop;

static class TestDescription_suite_StackTestSuite_TestCopyConstructor : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_StackTestSuite_TestCopyConstructor() : CxxTest::RealTestDescription( Tests_StackTestSuite, suiteDescription_StackTestSuite, 88, "TestCopyConstructor" ) {}
 void runTest() { suite_StackTestSuite.TestCopyConstructor(); }
} testDescription_suite_StackTestSuite_TestCopyConstructor;

static class TestDescription_suite_StackTestSuite_TestEqualsOperator : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_StackTestSuite_TestEqualsOperator() : CxxTest::RealTestDescription( Tests_StackTestSuite, suiteDescription_StackTestSuite, 101, "TestEqualsOperator" ) {}
 void runTest() { suite_StackTestSuite.TestEqualsOperator(); }
} testDescription_suite_StackTestSuite_TestEqualsOperator;

