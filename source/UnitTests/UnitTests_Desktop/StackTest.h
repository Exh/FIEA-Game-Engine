#pragma once

#include <cxxtest/TestSuite.h>
#include "vld.h"

#include "Foo.h"
#include "stack.h"

using namespace Library;
using namespace Test;

class StackTestSuite : public CxxTest::TestSuite
{
public:
	void setUp()
	{
		TS_ASSERT(mIntStack.IsEmpty());
		TS_ASSERT(mFooStack.IsEmpty());
		TS_ASSERT(mFooStarStack.IsEmpty());

		TS_ASSERT_EQUALS(mIntStack.Size(),0);
		TS_ASSERT_EQUALS(mFooStack.Size(),0);
		TS_ASSERT_EQUALS(mFooStarStack.Size(), 0);
	}

	void tearDown()
	{
		mIntStack.Clear();
		mFooStack.Clear();
		mFooStarStack.Clear();

		TS_ASSERT(mIntStack.IsEmpty());
		TS_ASSERT(mFooStack.IsEmpty());
		TS_ASSERT(mFooStarStack.IsEmpty());
	}

	void TestPushAndTop()
	{
		//testing empty stack
		TS_ASSERT_THROWS(mIntStack.Top(), std::exception);

		mIntStack.Push(10);
		mIntStack.Push(20);
		TS_ASSERT_EQUALS(mIntStack.Size(), 2);
		TS_ASSERT_EQUALS(mIntStack.Top(), 20);

		Foo foo1('a');
		Foo foo2('b');
		mFooStack.Push(foo2);
		TS_ASSERT_EQUALS(mFooStack.Top().GetID(), 'b');
		mFooStack.Push(foo1);
		TS_ASSERT_EQUALS(mFooStack.Top().GetID(), 'a');
		TS_ASSERT_EQUALS(mFooStack.Size(), 2);

		Foo* foo3 = new Foo('c');
		Foo* foo4 = new Foo('d');
		mFooStarStack.Push(foo3);
		mFooStarStack.Push(foo4);
		TS_ASSERT_EQUALS(mFooStarStack.Size(), 2);
		TS_ASSERT_EQUALS(mFooStarStack.Top()->GetID(), 'd');
		delete foo3;
		delete foo4;
	}


	void TestPop()
	{
		int ItemsArray[8] = { 1, 22, 5, 3, 97, 250, 1000, 4 };

		for (int i = 0; i < 8; i++)
		{
			mIntStack.Push(ItemsArray[i]);
		}
		TS_ASSERT_EQUALS(mIntStack.Size(), 8);
		TS_ASSERT_EQUALS(mIntStack.Top(), 4);

		//traversing in reverse since stack is LIFO
		for (int i = 7; i >= 0; i--)
		{
			int temp = mIntStack.Pop();
			TS_ASSERT_EQUALS(temp, ItemsArray[i]);
		}

		TS_ASSERT_EQUALS(mIntStack.Size(), 0);
		TS_ASSERT_THROWS(mIntStack.Top(),std::exception);
	}

	void TestCopyConstructor()
	{
		Foo foo1('1');
		mFooStack.Push(foo1);
		Stack<Foo> anotherFooStack = mFooStack;
		TS_ASSERT_EQUALS(anotherFooStack.Top().GetID(), '1');
		TS_ASSERT_EQUALS(anotherFooStack.Size(), mFooStack.Size());

		Stack<Foo*> anotherFooStarStack = mFooStarStack;
		TS_ASSERT_EQUALS(anotherFooStarStack.Size(), mFooStarStack.Size());
		TS_ASSERT_THROWS(anotherFooStarStack.Top(), std::exception);
	}

	void TestEqualsOperator()
	{
		Foo foo1('1');
		mFooStack.Push(foo1);
		Stack<Foo> anotherFooStack;
		anotherFooStack = mFooStack;
		TS_ASSERT_EQUALS(anotherFooStack.Top().GetID(), '1');
		TS_ASSERT_EQUALS(anotherFooStack.Size(), mFooStack.Size());

		Stack<Foo*> anotherFooStarStack; 
		anotherFooStarStack = mFooStarStack;
		TS_ASSERT_EQUALS(anotherFooStarStack.Size(), mFooStarStack.Size());
		TS_ASSERT_THROWS(anotherFooStarStack.Top(), std::exception);
	}


private:
	Stack<int> mIntStack;
	Stack<Foo> mFooStack;
	Stack<Foo*> mFooStarStack;
};