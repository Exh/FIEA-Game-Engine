/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>

bool suite_FactoryTestSuite_init = false;
#include "FactoryTestSuite.h"

static FactoryTestSuite suite_FactoryTestSuite;

static CxxTest::List Tests_FactoryTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_FactoryTestSuite( "C:/dev/students/ch11/srajanswain/Programming 2/FieaGameEngine/source/UnitTests/UnitTests_Desktop/FactoryTestSuite.h", 13, "FactoryTestSuite", suite_FactoryTestSuite, Tests_FactoryTestSuite );

static class TestDescription_suite_FactoryTestSuite_TestFactoryRegister : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FactoryTestSuite_TestFactoryRegister() : CxxTest::RealTestDescription( Tests_FactoryTestSuite, suiteDescription_FactoryTestSuite, 19, "TestFactoryRegister" ) {}
 void runTest() { suite_FactoryTestSuite.TestFactoryRegister(); }
} testDescription_suite_FactoryTestSuite_TestFactoryRegister;

static class TestDescription_suite_FactoryTestSuite_TestFind : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FactoryTestSuite_TestFind() : CxxTest::RealTestDescription( Tests_FactoryTestSuite, suiteDescription_FactoryTestSuite, 38, "TestFind" ) {}
 void runTest() { suite_FactoryTestSuite.TestFind(); }
} testDescription_suite_FactoryTestSuite_TestFind;

static class TestDescription_suite_FactoryTestSuite_TestCreate : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FactoryTestSuite_TestCreate() : CxxTest::RealTestDescription( Tests_FactoryTestSuite, suiteDescription_FactoryTestSuite, 49, "TestCreate" ) {}
 void runTest() { suite_FactoryTestSuite.TestCreate(); }
} testDescription_suite_FactoryTestSuite_TestCreate;

static class TestDescription_suite_FactoryTestSuite_TestIteration : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FactoryTestSuite_TestIteration() : CxxTest::RealTestDescription( Tests_FactoryTestSuite, suiteDescription_FactoryTestSuite, 69, "TestIteration" ) {}
 void runTest() { suite_FactoryTestSuite.TestIteration(); }
} testDescription_suite_FactoryTestSuite_TestIteration;

static class TestDescription_suite_FactoryTestSuite_TestClassName : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FactoryTestSuite_TestClassName() : CxxTest::RealTestDescription( Tests_FactoryTestSuite, suiteDescription_FactoryTestSuite, 85, "TestClassName" ) {}
 void runTest() { suite_FactoryTestSuite.TestClassName(); }
} testDescription_suite_FactoryTestSuite_TestClassName;

static class TestDescription_suite_FactoryTestSuite_TestAdd : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FactoryTestSuite_TestAdd() : CxxTest::RealTestDescription( Tests_FactoryTestSuite, suiteDescription_FactoryTestSuite, 94, "TestAdd" ) {}
 void runTest() { suite_FactoryTestSuite.TestAdd(); }
} testDescription_suite_FactoryTestSuite_TestAdd;

static class TestDescription_suite_FactoryTestSuite_TestRemove : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FactoryTestSuite_TestRemove() : CxxTest::RealTestDescription( Tests_FactoryTestSuite, suiteDescription_FactoryTestSuite, 108, "TestRemove" ) {}
 void runTest() { suite_FactoryTestSuite.TestRemove(); }
} testDescription_suite_FactoryTestSuite_TestRemove;

