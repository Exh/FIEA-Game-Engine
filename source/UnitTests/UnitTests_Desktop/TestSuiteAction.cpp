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

bool suite_TestSuiteAction_init = false;
#include "TestSuiteAction.h"

static TestSuiteAction suite_TestSuiteAction;

static CxxTest::List Tests_TestSuiteAction = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TestSuiteAction( "C:/dev/students/ch11/srajanswain/Programming 2/FieaGameEngine/source/UnitTests/UnitTests_Desktop/TestSuiteAction.h", 14, "TestSuiteAction", suite_TestSuiteAction, Tests_TestSuiteAction );

static class TestDescription_suite_TestSuiteAction_TestConstruction : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestSuiteAction_TestConstruction() : CxxTest::RealTestDescription( Tests_TestSuiteAction, suiteDescription_TestSuiteAction, 17, "TestConstruction" ) {}
 void runTest() { suite_TestSuiteAction.TestConstruction(); }
} testDescription_suite_TestSuiteAction_TestConstruction;

static class TestDescription_suite_TestSuiteAction_TestMoveAction : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestSuiteAction_TestMoveAction() : CxxTest::RealTestDescription( Tests_TestSuiteAction, suiteDescription_TestSuiteAction, 32, "TestMoveAction" ) {}
 void runTest() { suite_TestSuiteAction.TestMoveAction(); }
} testDescription_suite_TestSuiteAction_TestMoveAction;

static class TestDescription_suite_TestSuiteAction_TestCreateAction : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestSuiteAction_TestCreateAction() : CxxTest::RealTestDescription( Tests_TestSuiteAction, suiteDescription_TestSuiteAction, 86, "TestCreateAction" ) {}
 void runTest() { suite_TestSuiteAction.TestCreateAction(); }
} testDescription_suite_TestSuiteAction_TestCreateAction;

static class TestDescription_suite_TestSuiteAction_TestUpdate : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestSuiteAction_TestUpdate() : CxxTest::RealTestDescription( Tests_TestSuiteAction, suiteDescription_TestSuiteAction, 131, "TestUpdate" ) {}
 void runTest() { suite_TestSuiteAction.TestUpdate(); }
} testDescription_suite_TestSuiteAction_TestUpdate;

static class TestDescription_suite_TestSuiteAction_TestCreateWithoutFactory : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestSuiteAction_TestCreateWithoutFactory() : CxxTest::RealTestDescription( Tests_TestSuiteAction, suiteDescription_TestSuiteAction, 153, "TestCreateWithoutFactory" ) {}
 void runTest() { suite_TestSuiteAction.TestCreateWithoutFactory(); }
} testDescription_suite_TestSuiteAction_TestCreateWithoutFactory;

static class TestDescription_suite_TestSuiteAction_TestCreateActionIfFromXml : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestSuiteAction_TestCreateActionIfFromXml() : CxxTest::RealTestDescription( Tests_TestSuiteAction, suiteDescription_TestSuiteAction, 181, "TestCreateActionIfFromXml" ) {}
 void runTest() { suite_TestSuiteAction.TestCreateActionIfFromXml(); }
} testDescription_suite_TestSuiteAction_TestCreateActionIfFromXml;

static class TestDescription_suite_TestSuiteAction_TestIf : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestSuiteAction_TestIf() : CxxTest::RealTestDescription( Tests_TestSuiteAction, suiteDescription_TestSuiteAction, 259, "TestIf" ) {}
 void runTest() { suite_TestSuiteAction.TestIf(); }
} testDescription_suite_TestSuiteAction_TestIf;

