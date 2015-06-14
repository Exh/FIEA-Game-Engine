/**	@file SListTest.h
*	Contains unit tests for Slist
*/
#pragma once

#include <string>
#include <stdexcept>
#include <exception>
#include <cstdint>
#include <cxxtest/TestSuite.h>
#include "vld.h"

#include "Slist.h"
#include "Foo.h"

using namespace Library;
using namespace Test;

/** @class CxxTest class to unit test Slist */
class SListTestSuite : public CxxTest::TestSuite
{
public:
	/**	Method to set up data for test. This is executed before each test */
	void setUp()
	{
		TS_ASSERT(mCharList.IsEmpty());
		TS_ASSERT(mIntList.IsEmpty());
		TS_ASSERT(mFooList.IsEmpty());
		TS_ASSERT(mIntStarList.IsEmpty());
	}

	/**	Method to clean up the data after the test. This is executed after each test */
	void tearDown()
	{
		mIntList.Clear();
		mCharList.Clear();
		mFooList.Clear();
		mIntStarList.Clear();

		TS_ASSERT_EQUALS(mCharList.Size(), 0);
		TS_ASSERT_EQUALS(mIntList.Size(), 0);
		TS_ASSERT_EQUALS(mFooList.Size(), 0);
		TS_ASSERT_EQUALS(mIntStarList.Size(), 0);
	}

	/** Method to test Front() and Back() on an empty list. Tests on other lists included in other methods */
	void TestEmptyListFrontAndBack()
	{
		TS_ASSERT_THROWS(mCharList.Front(),std::exception);
		TS_ASSERT_THROWS(mCharList.Back(),std::exception);
	}

	void TestPushBack()
	{
		//on int list
		mIntList.PushBack(10);
		TS_ASSERT_EQUALS(mIntList.Size(), 1);
		TS_ASSERT_EQUALS(mIntList.Front(), 10);
		TS_ASSERT_EQUALS(mIntList.Back(), 10);

		//appending duplicate values in Foo list
		Foo foo('1');
		mFooList.PushBack(foo);
		mFooList.PushBack(foo);
		TS_ASSERT_EQUALS(mFooList.Size(), 2);
		TS_ASSERT_EQUALS(mFooList.Front().GetID(), '1');
		mFooList.PopFront();
		TS_ASSERT_EQUALS(mFooList.Back().GetID(), '1');

		//on int* star
		int a = 10;
		int b = 20;
		int c = 30;
		mIntStarList.PushBack(&a);
		mIntStarList.PushBack(&b);
		mIntStarList.PushBack(&c);
		TS_ASSERT_EQUALS(mIntStarList.Size(), 3);
		TS_ASSERT_EQUALS(*mIntStarList.Front(), a);
		TS_ASSERT_EQUALS(*mIntStarList.Back(), c);
	}

	void TestPushFront()
	{
		//on int list
		mIntList.PushBack(10);
		mIntList.PushFront(20);
		TS_ASSERT_EQUALS(mIntList.Size(), 2);
		TS_ASSERT_EQUALS(mIntList.Front(), 20);
		TS_ASSERT_EQUALS(mIntList.Back(), 10);

		//inserting duplicate values in Foo list
		Foo tempFoo('1');
		mFooList.PushFront(tempFoo);
		mFooList.PushFront(tempFoo);
		TS_ASSERT_EQUALS(mFooList.Size(), 2);
		TS_ASSERT_EQUALS(mFooList.Front(), tempFoo);
		mFooList.PopFront();
		TS_ASSERT_EQUALS(mFooList.Front(), tempFoo);

		//on int* list
		int a = 40;
		mIntStarList.PushFront(&a);
		TS_ASSERT_EQUALS(mIntStarList.Size(), 1);
		TS_ASSERT_EQUALS(*mIntStarList.Front(), a);
	}

	void TestPopFront()
	{
		//popping from an empty char list
		TS_ASSERT_THROWS(mCharList.PopFront(),std::exception);
		TS_ASSERT_EQUALS(mCharList.Size(), 0);
		
		//on int list
		mIntList.PushBack(10);
		mIntList.PopFront();
		TS_ASSERT_EQUALS(mIntList.Size(), 0);

		//on Foo list
		Foo foo('1');
		mFooList.PushBack(foo);
		mFooList.PushBack(foo);
		mFooList.PopFront();
		TS_ASSERT_EQUALS(mFooList.Size(), 1);
		TS_ASSERT_EQUALS(mFooList.Front().GetID(), '1');
		TS_ASSERT_EQUALS(mFooList.Back().GetID(), '1');

		//on int* list
		int a = 10;
		int b = 20;
		int c = 30;
		mIntStarList.PushBack(&a);
		mIntStarList.PushBack(&b);
		mIntStarList.PushBack(&c);
		mIntStarList.PopFront();
		TS_ASSERT_EQUALS(mIntStarList.Size(), 2);
		TS_ASSERT_EQUALS(*mIntStarList.Front(), b);
		TS_ASSERT_EQUALS(*mIntStarList.Back(), c);
	}

	void TestPushFrontAndBack()
	{
		//on char list
		mCharList.PushFront('x');
		mCharList.PushBack('y');
		TS_ASSERT_EQUALS(mCharList.Front(), 'x');
		TS_ASSERT_EQUALS(mCharList.Back(), 'y');

		//on int list
		mIntList.PushFront(10);
		mIntList.PushBack(20);
		TS_ASSERT_EQUALS(mIntList.Front(), 10);
		TS_ASSERT_EQUALS(mIntList.Back(), 20);

		//on Foo list
		Foo foo('1');
		mFooList.PushFront(foo);
		mFooList.PushBack(foo);
		TS_ASSERT_EQUALS(mFooList.Front(), foo);
		TS_ASSERT_EQUALS(mFooList.Back(), foo);

		//on int* list
		int a = 10;
		int b = 20;
		mIntStarList.PushFront(&a);
		mIntStarList.PushBack(&b);
		TS_ASSERT_EQUALS(*mIntStarList.Front(), a);
		TS_ASSERT_EQUALS(*mIntStarList.Back(), b);
	}

	void TestPushBackAndFront()
	{
		//on char list
		mCharList.PushBack('x');
		mCharList.PushFront('y');
		TS_ASSERT_EQUALS(mCharList.Front(), 'y');
		TS_ASSERT_EQUALS(mCharList.Back(), 'x');

		//on int list
		mIntList.PushBack(10);
		mIntList.PushFront(20);
		TS_ASSERT_EQUALS(mIntList.Front(), 20);
		TS_ASSERT_EQUALS(mIntList.Back(), 10);

		//on Foo list
		Foo foo1('1');
		mFooList.PushBack(foo1);
		Foo foo2('2');
		mFooList.PushBack(foo2);
		mFooList.PushFront(foo2);
		TS_ASSERT_EQUALS(mFooList.Front(), foo2);
		TS_ASSERT_EQUALS(mFooList.Back(), foo2);

		//on int* list
		int a = 10;
		int b = 20;
		mIntStarList.PushBack(&a);
		mIntStarList.PushFront(&b);
		TS_ASSERT_EQUALS(*mIntStarList.Front(), b);
		TS_ASSERT_EQUALS(*mIntStarList.Back(), a);
	}

	/** To test deep copy using = operator */
	void TestEqualsOperator()
	{
		//copying empty char list
		SList<char> copyCharList;
		copyCharList = mCharList;
		TS_ASSERT_EQUALS(copyCharList.Size(), mCharList.Size());
		TS_ASSERT_THROWS(copyCharList.Front(),std::exception);
		TS_ASSERT_THROWS(copyCharList.Back(),std::exception);

		//copy int list
		mIntList.PushBack(10);
		
		SList<int> copyIntList;
		copyIntList = mIntList;
		TS_ASSERT_EQUALS(copyIntList.Size(), mIntList.Size());
		TS_ASSERT_EQUALS(copyIntList.Front(), mIntList.Front());
		TS_ASSERT_EQUALS(copyIntList.Back(), mIntList.Back());

		//copy Foo list
		Foo foo('1');
		mFooList.PushBack(foo);
		mFooList.PushBack(foo);

		SList<Foo> copyFooList;
		copyFooList = mFooList;
		TS_ASSERT_EQUALS(copyFooList.Size(), mFooList.Size());
		TS_ASSERT_EQUALS(copyFooList.Front(), mFooList.Front());
		TS_ASSERT_EQUALS(copyFooList.Back(), mFooList.Back());

		//copy int* list
		int a = 10;
		int b = 20;
		mIntStarList.PushBack(&a);
		mIntStarList.PushFront(&b);

		SList<int*> copyIntStarList;
		copyIntStarList = mIntStarList;
		TS_ASSERT_EQUALS(copyIntStarList.Size(), mIntStarList.Size());
		TS_ASSERT_EQUALS(copyIntStarList.Front(), mIntStarList.Front());
		TS_ASSERT_EQUALS(copyIntStarList.Back(), mIntStarList.Back());
	}

	/** Testing deep copy using copy constructor */
	void TestCopyConstructor()
	{
		//copying empty char list
		SList<char> copyCharList(mCharList);
		TS_ASSERT_EQUALS(copyCharList.Size(), mCharList.Size());
		TS_ASSERT_THROWS(copyCharList.Front(), std::exception);
		TS_ASSERT_THROWS(copyCharList.Back(), std::exception);

		//copy int list
		mIntList.PushBack(10);
		SList<int> copyIntList(mIntList);
		TS_ASSERT_EQUALS(copyIntList.Size(), mIntList.Size());
		TS_ASSERT_EQUALS(copyIntList.Front(), mIntList.Front());
		TS_ASSERT_EQUALS(copyIntList.Back(), mIntList.Back());

		//copy Foo list
		Foo foo('7');
		mFooList.PushBack(foo);
		mFooList.PushBack(foo);
		SList<Foo> copyFooList(mFooList);
		TS_ASSERT_EQUALS(copyFooList.Size(), mFooList.Size());
		TS_ASSERT_EQUALS(copyFooList.Front(), mFooList.Front());
		TS_ASSERT_EQUALS(copyFooList.Back(), mFooList.Back());

		//copy int* list
		int a = 10;
		int b = 20;
		mIntStarList.PushBack(&a);
		mIntStarList.PushFront(&b);
		SList<int*> copyIntStarList(mIntStarList);
		TS_ASSERT_EQUALS(copyIntStarList.Size(), mIntStarList.Size());
		TS_ASSERT_EQUALS(copyIntStarList.Front(), mIntStarList.Front());
		TS_ASSERT_EQUALS(copyIntStarList.Back(), mIntStarList.Back());
	}

	void TestIteratorTraversal()
	{
		mIntList.PushBack(1);
		mIntList.PushBack(2);
		mIntList.PushBack(3);
		mIntList.PushBack(4);
		auto copyIntList = mIntList;

		std::uint32_t count = 0;
		//check if the iterator traverses the whole list correctly
		for (auto it = mIntList.begin(); it != mIntList.end(); ++it)
		{
			++count;
			//iterator de-refernce
			TS_ASSERT_EQUALS(*it, copyIntList.Front());
			copyIntList.PopFront();
		}

		TS_ASSERT_EQUALS(mIntList.Size(), count);
	}

	void TestIteratorInsert()
	{
		//insert after in empty list
		mIntList.InsertAfter(mIntList.begin(), 10);
		TS_ASSERT_EQUALS(mIntList.Size(), 1);
		TS_ASSERT_EQUALS(mIntList.Front(), 10);
		
		//normal insert after
		mIntList.InsertAfter(mIntList.begin(), 20);

		//insert after end of list
		mIntList.InsertAfter(mIntList.end(), 30);

		//checking if inserted correctly
		TS_ASSERT_EQUALS(mIntList.Front(), 10);
		mIntList.PopFront();
		TS_ASSERT_EQUALS(mIntList.Front(), 20);
		mIntList.PopFront();
		TS_ASSERT_EQUALS(mIntList.Front(), 30);
	}

	void TestIteratorRemove()
	{
		mIntList.PushBack(10);
		mIntList.PushBack(20);
		mIntList.PushBack(30);
		mIntList.PushBack(40);
		mIntList.PushBack(50);

		//remove an element that is present in the list
		mIntList.Remove(30);
		TS_ASSERT_EQUALS(mIntList.Size(), 4);

		//remove one that is not present
		mIntList.Remove(0);
		TS_ASSERT_EQUALS(mIntList.Size(), 4);

		//remove from front of list
		mIntList.Remove(10);
		TS_ASSERT_EQUALS(mIntList.Size(), 3);

		//remove from end of the list
		mIntList.Remove(50);
		TS_ASSERT_EQUALS(mIntList.Size(), 2);

		//normal remove
		mIntList.Remove(40);
		TS_ASSERT_EQUALS(mIntList.Size(), 1);

		mIntList.Remove(20);
		TS_ASSERT_EQUALS(mIntList.Size(), 0);

		//remove from an empty list
		mIntList.Remove(30);
		TS_ASSERT_EQUALS(mIntList.Size(), 0);
	}

	void TestIteratorFind()
	{
		mIntList.PushBack(10);
		mIntList.PushBack(20);
		mIntList.PushBack(30);
		auto it = mIntList.begin();

		//iterator copy constructor
		//find an item that's present in the list
		auto anotherIt = mIntList.Find(20);
		//iterator pre-increment
		TS_ASSERT_EQUALS(++it, anotherIt);

		//find an item that's not in the list
		anotherIt = mIntList.Find(0);
		TS_ASSERT_EQUALS(anotherIt, mIntList.end());

		//find in an empty list
		TS_ASSERT_EQUALS(mCharList.Find('x'), mCharList.end());
	}

	void TestIteratorCopy()
	{
		mIntList.PushBack(10);
		mIntList.PushBack(20);
		mIntList.PushBack(30);
		auto it = mIntList.begin();

		//iterator assignment
		SList<int>::Iterator anotherIt;
		anotherIt = mIntList.begin();

		TS_ASSERT_EQUALS(it, anotherIt);

		//copy empty iterator
		auto it1 = mCharList.begin();
		SList<char>::Iterator charIt;
		charIt = it1;
		TS_ASSERT_EQUALS(it1, charIt);
	}

	void TestIteratorEquality()
	{
		mIntList.PushBack(10);
		mIntList.PushBack(20);
		mIntList.PushBack(30);

		//comparing to itself
		auto it = mIntList.begin();
		TS_ASSERT(it == it);

		//iterator post-increment
		auto anotherIt = it++;
		TS_ASSERT_DIFFERS(anotherIt, it);
		//iterator !=
		TS_ASSERT(anotherIt != it);

		//iterator pre-increment
		++anotherIt;
		TS_ASSERT(anotherIt == it);
	}

private:
	SList<int> mIntList;		//a list that is mostly going to have just one value
	SList<char> mCharList;		//a list that is going to be empty for the most part
	SList<int*> mIntStarList;	//for testing pointers
	SList<Foo> mFooList;		//for testing user defined types
};