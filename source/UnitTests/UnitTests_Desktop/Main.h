#pragma once

#include <cxxtest/TestSuite.h>

/**
Class to generate Main for Unit Test Classes using CxxTest
*/
class SampleTestSuite : public CxxTest::TestSuite
{
public:
	void TestAddition(void)
	{
		TS_ASSERT_EQUALS(1 + 1, 2);
	}
};