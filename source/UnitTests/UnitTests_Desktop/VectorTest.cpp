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

bool suite_VectorTestSuite_init = false;
#include "VectorTest.h"

static VectorTestSuite suite_VectorTestSuite;

static CxxTest::List Tests_VectorTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_VectorTestSuite( "C:/dev/students/ch11/srajanswain/Programming 2/FieaGameEngine/source/UnitTests/UnitTests_Desktop/VectorTest.h", 13, "VectorTestSuite", suite_VectorTestSuite, Tests_VectorTestSuite );

static class TestDescription_suite_VectorTestSuite_TestIsEmpty : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestIsEmpty() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 17, "TestIsEmpty" ) {}
 void runTest() { suite_VectorTestSuite.TestIsEmpty(); }
} testDescription_suite_VectorTestSuite_TestIsEmpty;

static class TestDescription_suite_VectorTestSuite_TestSize : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestSize() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 28, "TestSize" ) {}
 void runTest() { suite_VectorTestSuite.TestSize(); }
} testDescription_suite_VectorTestSuite_TestSize;

static class TestDescription_suite_VectorTestSuite_TestCapacity : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestCapacity() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 39, "TestCapacity" ) {}
 void runTest() { suite_VectorTestSuite.TestCapacity(); }
} testDescription_suite_VectorTestSuite_TestCapacity;

static class TestDescription_suite_VectorTestSuite_TestPushBack : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestPushBack() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 50, "TestPushBack" ) {}
 void runTest() { suite_VectorTestSuite.TestPushBack(); }
} testDescription_suite_VectorTestSuite_TestPushBack;

static class TestDescription_suite_VectorTestSuite_TestClear : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestClear() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 83, "TestClear" ) {}
 void runTest() { suite_VectorTestSuite.TestClear(); }
} testDescription_suite_VectorTestSuite_TestClear;

static class TestDescription_suite_VectorTestSuite_TestReserve : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestReserve() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 117, "TestReserve" ) {}
 void runTest() { suite_VectorTestSuite.TestReserve(); }
} testDescription_suite_VectorTestSuite_TestReserve;

static class TestDescription_suite_VectorTestSuite_TestPopBack : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestPopBack() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 148, "TestPopBack" ) {}
 void runTest() { suite_VectorTestSuite.TestPopBack(); }
} testDescription_suite_VectorTestSuite_TestPopBack;

static class TestDescription_suite_VectorTestSuite_TestFind : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestFind() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 176, "TestFind" ) {}
 void runTest() { suite_VectorTestSuite.TestFind(); }
} testDescription_suite_VectorTestSuite_TestFind;

static class TestDescription_suite_VectorTestSuite_TestFrontBackOnEmpty : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestFrontBackOnEmpty() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 213, "TestFrontBackOnEmpty" ) {}
 void runTest() { suite_VectorTestSuite.TestFrontBackOnEmpty(); }
} testDescription_suite_VectorTestSuite_TestFrontBackOnEmpty;

static class TestDescription_suite_VectorTestSuite_TestCtorDtor : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestCtorDtor() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 221, "TestCtorDtor" ) {}
 void runTest() { suite_VectorTestSuite.TestCtorDtor(); }
} testDescription_suite_VectorTestSuite_TestCtorDtor;

static class TestDescription_suite_VectorTestSuite_TestRemoveOneItem : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestRemoveOneItem() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 229, "TestRemoveOneItem" ) {}
 void runTest() { suite_VectorTestSuite.TestRemoveOneItem(); }
} testDescription_suite_VectorTestSuite_TestRemoveOneItem;

static class TestDescription_suite_VectorTestSuite_TestRemoveUsingIterators : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestRemoveUsingIterators() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 278, "TestRemoveUsingIterators" ) {}
 void runTest() { suite_VectorTestSuite.TestRemoveUsingIterators(); }
} testDescription_suite_VectorTestSuite_TestRemoveUsingIterators;

static class TestDescription_suite_VectorTestSuite_TestRemoveIterator : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestRemoveIterator() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 310, "TestRemoveIterator" ) {}
 void runTest() { suite_VectorTestSuite.TestRemoveIterator(); }
} testDescription_suite_VectorTestSuite_TestRemoveIterator;

static class TestDescription_suite_VectorTestSuite_TestAddAfterRemove : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestAddAfterRemove() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 334, "TestAddAfterRemove" ) {}
 void runTest() { suite_VectorTestSuite.TestAddAfterRemove(); }
} testDescription_suite_VectorTestSuite_TestAddAfterRemove;

static class TestDescription_suite_VectorTestSuite_TestIndexing : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestIndexing() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 365, "TestIndexing" ) {}
 void runTest() { suite_VectorTestSuite.TestIndexing(); }
} testDescription_suite_VectorTestSuite_TestIndexing;

static class TestDescription_suite_VectorTestSuite_TestEqualsOperator : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestEqualsOperator() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 393, "TestEqualsOperator" ) {}
 void runTest() { suite_VectorTestSuite.TestEqualsOperator(); }
} testDescription_suite_VectorTestSuite_TestEqualsOperator;

static class TestDescription_suite_VectorTestSuite_TestVectorCopyConstructor : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestVectorCopyConstructor() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 410, "TestVectorCopyConstructor" ) {}
 void runTest() { suite_VectorTestSuite.TestVectorCopyConstructor(); }
} testDescription_suite_VectorTestSuite_TestVectorCopyConstructor;

static class TestDescription_suite_VectorTestSuite_TestAt : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestAt() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 426, "TestAt" ) {}
 void runTest() { suite_VectorTestSuite.TestAt(); }
} testDescription_suite_VectorTestSuite_TestAt;

static class TestDescription_suite_VectorTestSuite_TestIteratorCopyConstructor : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestIteratorCopyConstructor() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 445, "TestIteratorCopyConstructor" ) {}
 void runTest() { suite_VectorTestSuite.TestIteratorCopyConstructor(); }
} testDescription_suite_VectorTestSuite_TestIteratorCopyConstructor;

static class TestDescription_suite_VectorTestSuite_TestIteratorEqualsOperator : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestIteratorEqualsOperator() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 465, "TestIteratorEqualsOperator" ) {}
 void runTest() { suite_VectorTestSuite.TestIteratorEqualsOperator(); }
} testDescription_suite_VectorTestSuite_TestIteratorEqualsOperator;

static class TestDescription_suite_VectorTestSuite_TestIteration : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestIteration() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 489, "TestIteration" ) {}
 void runTest() { suite_VectorTestSuite.TestIteration(); }
} testDescription_suite_VectorTestSuite_TestIteration;

static class TestDescription_suite_VectorTestSuite_TestIteratorEquality : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestIteratorEquality() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 507, "TestIteratorEquality" ) {}
 void runTest() { suite_VectorTestSuite.TestIteratorEquality(); }
} testDescription_suite_VectorTestSuite_TestIteratorEquality;

static class TestDescription_suite_VectorTestSuite_TestIteratorPostIncrement : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestIteratorPostIncrement() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 520, "TestIteratorPostIncrement" ) {}
 void runTest() { suite_VectorTestSuite.TestIteratorPostIncrement(); }
} testDescription_suite_VectorTestSuite_TestIteratorPostIncrement;

static class TestDescription_suite_VectorTestSuite_TestIteratorSubtract : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_TestIteratorSubtract() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 533, "TestIteratorSubtract" ) {}
 void runTest() { suite_VectorTestSuite.TestIteratorSubtract(); }
} testDescription_suite_VectorTestSuite_TestIteratorSubtract;

