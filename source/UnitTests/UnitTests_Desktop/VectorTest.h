#pragma once

#include <cxxtest/TestSuite.h>
#include "vld.h"

#include "vector.h"
#include "Foo.h"
#include "FooFunctor.h"

using namespace Library;
using namespace Test;

class VectorTestSuite : public CxxTest::TestSuite
{
public:

	void TestIsEmpty()
	{
		Vector<int> intVector;
		Vector<Foo, FooFunctor> fooVector;
		Vector<int*> intStarVector;

		TS_ASSERT(intVector.IsEmpty());
		TS_ASSERT(intStarVector.IsEmpty());
		TS_ASSERT(fooVector.IsEmpty());
	}

	void TestSize()
	{
		Vector<int> intVector;
		Vector<Foo, FooFunctor> fooVector;
		Vector<int*> intStarVector;

		TS_ASSERT_EQUALS(intVector.Size(), 0);
		TS_ASSERT_EQUALS(intStarVector.Size(), 0);
		TS_ASSERT_EQUALS(fooVector.Size(), 0);
	}

	void TestCapacity()
	{
		Vector<int> intVector;
		Vector<Foo, FooFunctor> fooVector;
		Vector<int*> intStarVector;

		TS_ASSERT_EQUALS(intVector.Capacity(), 0);
		TS_ASSERT_EQUALS(intStarVector.Capacity(), 0);
		TS_ASSERT_EQUALS(fooVector.Capacity(), 0);
	}

	void TestPushBack()
	{
		Vector<int> intVector;
		Vector<Foo, FooFunctor> fooVector;
		Vector<int*> intStarVector;

		intVector.PushBack(1);
		TS_ASSERT_EQUALS(intVector.Size(), 1);
		TS_ASSERT_EQUALS(intVector.Capacity(), 1);
		TS_ASSERT_EQUALS(intVector.Front(), 1);
		TS_ASSERT_EQUALS(intVector.Back(), 1);

		int a = 10;
		int b = 20;
		int c = 30;
		intStarVector.PushBack(&a); //capacity is 1, this pushback doesnt reserve
		intStarVector.PushBack(&b); //but this one does. capacity=2
		intStarVector.PushBack(&c); //and so does this one. capacity=4
		TS_ASSERT_EQUALS(intStarVector.Size(), 3);
		TS_ASSERT_EQUALS(intStarVector.Capacity(), 4);
		TS_ASSERT_EQUALS(*intStarVector.Front(), 10);
		TS_ASSERT_EQUALS(*intStarVector.Back(), 30);

		Foo foo1('a');
		Foo foo2('b');
		fooVector.PushBack(foo1);
		fooVector.PushBack(foo2);
		TS_ASSERT_EQUALS(fooVector.Size(), 2);
		TS_ASSERT_EQUALS(fooVector.Capacity(), 3);
		TS_ASSERT_EQUALS(fooVector.Front().GetID(), 'a');
		TS_ASSERT_EQUALS(fooVector.Back().GetID(), 'b');
	}

	void TestClear()
	{
		Vector<int> intVector;
		Vector<Foo, FooFunctor> fooVector;
		Vector<int*> intStarVector;
		
		//pushing some data just to clear
		intVector.PushBack(1);

		int a = 10;
		int b = 20;
		int c = 30;
		intStarVector.PushBack(&a);
		intStarVector.PushBack(&b);
		intStarVector.PushBack(&c);

		Foo foo1('a');
		Foo foo2('b');
		fooVector.PushBack(foo1);
		fooVector.PushBack(foo2);

		intVector.Clear();
		intStarVector.Clear();
		fooVector.Clear();

		TS_ASSERT_EQUALS(intVector.Size(), 0);
		TS_ASSERT_EQUALS(intStarVector.Size(), 0);
		TS_ASSERT_EQUALS(fooVector.Size(), 0);

		TS_ASSERT_EQUALS(intVector.Capacity(), 0);
		TS_ASSERT_EQUALS(intStarVector.Capacity(), 0);
		TS_ASSERT_EQUALS(fooVector.Capacity(), 0);
	}

	void TestReserve()
	{
		Vector<int> intVector;
		Vector<Foo, FooFunctor> fooVector;
		Vector<int*> intStarVector;

		intVector.Reserve(); //calling the functor
		TS_ASSERT_EQUALS(intVector.Capacity(), 1);
		intVector.Reserve(3); //normal reserve
		TS_ASSERT_EQUALS(intVector.Capacity(), 3);

		fooVector.Reserve();
		TS_ASSERT_EQUALS(fooVector.Capacity(), 3);
		fooVector.Reserve(6); //reserving equal to capacity
		TS_ASSERT_EQUALS(fooVector.Capacity(), 6);
		fooVector.Reserve(1); //reserving less than capacity
		TS_ASSERT_EQUALS(fooVector.Capacity(), 6);

		int a = 10;
		int b = 20;
		int c = 30;
		intStarVector.PushBack(&a);
		intStarVector.PushBack(&b);
		intStarVector.PushBack(&c);
		intStarVector.Reserve(10); //reserving with data in the container
		TS_ASSERT_EQUALS(intStarVector.Capacity(), 10);
		TS_ASSERT_EQUALS(intStarVector.Size(), 3);
		TS_ASSERT_EQUALS(*intStarVector.Front(), 10);
		TS_ASSERT_EQUALS(*intStarVector.Back(), 30);
	}

	void TestPopBack()
	{
		Vector<int> intVector;
		Vector<Foo, FooFunctor> fooVector;
		Vector<int*> intStarVector;

		//normal popback
		intVector.PushBack(10);
		intVector.PopBack();
		TS_ASSERT_EQUALS(intVector.Size(), 0);

		Foo foo1('a');
		Foo foo2('b');
		fooVector.PushBack(foo1);
		fooVector.PushBack(foo2);
		fooVector.PushBack(foo1);
		fooVector.PushBack(foo2);
		fooVector.PushBack(foo1);
		fooVector.PopBack();
		TS_ASSERT_EQUALS(fooVector.Size(), 4);
		TS_ASSERT_EQUALS(fooVector.Capacity(), 6);
		TS_ASSERT_EQUALS(fooVector.Front().GetID(), 'a');
		TS_ASSERT_EQUALS(fooVector.Back().GetID(), 'b');

		//popback on an empty vector
		TS_ASSERT_THROWS(intStarVector.PopBack(), std::out_of_range);
	}

	void TestFind()
	{
		Vector<int> intVector;
		Vector<int*> intStarVector;

		intVector.PushBack(1);
		intVector.PushBack(2);
		intVector.PushBack(3);
		intVector.PushBack(4);
		intVector.PushBack(5);
		intVector.PushBack(6);

		//finding an item that is present
		Vector<int>::Iterator it = intVector.Find(3);
		TS_ASSERT_DIFFERS(it, intVector.end());
		TS_ASSERT_EQUALS((*it), 3);

		//finding and item that is not present
		it = intVector.Find(7);
		TS_ASSERT_EQUALS(it, intVector.end());

		//item present at end of list
		it = intVector.Find(6);
		TS_ASSERT_DIFFERS(it, intVector.end());
		TS_ASSERT_EQUALS((*it), 6);

		//item found at beginning
		it = intVector.Find(1);
		TS_ASSERT_EQUALS(it, intVector.begin());
		TS_ASSERT_EQUALS((*it), 1);

		//finding in an empty vector
		int a = 1;
		Vector<int*>::Iterator it1 = intStarVector.Find(&a);
		TS_ASSERT_EQUALS(it1, intStarVector.end());
	}

	void TestFrontBackOnEmpty()
	{
		Vector<int*> intStarVector;

		TS_ASSERT_THROWS(intStarVector.Front(), std::out_of_range);
		TS_ASSERT_THROWS(intStarVector.Back(), std::out_of_range);
	}

	void TestCtorDtor()
	{
		Vector<char>* charVector = new Vector<char>(10);
		TS_ASSERT_EQUALS(charVector->Size(), 0);
		TS_ASSERT_EQUALS(charVector->Capacity(), 10);
		delete charVector;
	}

	void TestRemoveOneItem()
	{
		Vector<int> intVector;

		intVector.PushBack(1);
		intVector.PushBack(2);
		intVector.PushBack(3);
		intVector.PushBack(4);
		intVector.PushBack(5);
		intVector.PushBack(6);
		TS_ASSERT_EQUALS(intVector.Size(), 6);
		TS_ASSERT_EQUALS(intVector.Capacity(), 8);
		TS_ASSERT_EQUALS(intVector.Front(), 1);
		TS_ASSERT_EQUALS(intVector.Back(), 6);

		//remove an item in list
		intVector.Remove(4);
		TS_ASSERT_EQUALS(intVector.Size(), 5);
		TS_ASSERT_EQUALS(intVector.Capacity(), 8);

		//remove an item not in list
		intVector.Remove(4);
		TS_ASSERT_EQUALS(intVector.Size(), 5);
		TS_ASSERT_EQUALS(intVector.Capacity(), 8);

		//remove first item
		intVector.Remove(1);
		TS_ASSERT_EQUALS(intVector.Size(), 4);
		TS_ASSERT_EQUALS(intVector.Capacity(), 8);
		TS_ASSERT_EQUALS(intVector.Front(), 2);

		//remove last item
		intVector.Remove(6);
		TS_ASSERT_EQUALS(intVector.Size(), 3);
		TS_ASSERT_EQUALS(intVector.Capacity(), 8);
		TS_ASSERT_EQUALS(intVector.Back(), 5);

		Vector<Foo> fooVector;
		Foo foo1('a');
		Foo foo2('a');
		Foo foo3('a');
		fooVector.PushBack(foo1);
		fooVector.PushBack(foo2);
		fooVector.PushBack(foo3);
		fooVector.Remove(foo2);
		TS_ASSERT_EQUALS(fooVector.Size(), 2);
		
	}

	void TestRemoveUsingIterators()
	{
		Vector<int> intVector;
		intVector.PushBack(1);
		intVector.PushBack(2);
		intVector.PushBack(3);
		intVector.PushBack(4);
		intVector.PushBack(5);
		intVector.PushBack(6);

		//iterator from a different source
		Vector<int> mAnotherIntVector;
		TS_ASSERT_THROWS(intVector.Remove(mAnotherIntVector.begin(), intVector.Find(2)), std::exception);

		//end iterator
		TS_ASSERT_THROWS(intVector.Remove(intVector.begin(), intVector.end()), std::exception);

		//last before first
		TS_ASSERT_THROWS(intVector.Remove(intVector.Find(5), intVector.Find(2)), std::exception);

		//remove one item
		Vector<int>::Iterator it = intVector.Find(3);
		intVector.Remove(it, it);
		TS_ASSERT_EQUALS(intVector[2], 4);
		TS_ASSERT_EQUALS(intVector.Size(), 5);

		//remove range
		intVector.Remove(intVector.Find(2), intVector.Find(5));
		TS_ASSERT_EQUALS(intVector[1], 6);
		TS_ASSERT_EQUALS(intVector.Size(), 2);
	}

	void TestRemoveIterator()
	{
		Vector<int> intVector;
		intVector.PushBack(1);
		intVector.PushBack(2);
		intVector.PushBack(3);
		intVector.PushBack(4);
		intVector.PushBack(5);
		intVector.PushBack(6);

		//iterator from a different source
		Vector<int> mAnotherIntVector;
		TS_ASSERT_THROWS(intVector.Remove(mAnotherIntVector.begin()), std::exception);

		//end iterator
		TS_ASSERT_THROWS(intVector.Remove(intVector.end()), std::exception);

		//plain old remove 
		Vector<int>::Iterator it = intVector.Find(3);
		intVector.Remove(it, it);
		TS_ASSERT_EQUALS(intVector[2], 4);
		TS_ASSERT_EQUALS(intVector.Size(), 5);
	}

	void TestAddAfterRemove()
	{
		Vector<int> intVector;
		intVector.PushBack(1);
		intVector.PushBack(2);
		intVector.PushBack(3);

		intVector.Remove(2);
		intVector.PushBack(4);
		TS_ASSERT_EQUALS(intVector.Size(), 3);
		TS_ASSERT_EQUALS(intVector.Back(), 4);

		Vector<Foo*> fooStarVector;
		Foo* foo1 = new Foo('a');
		Foo* foo2 = new Foo('b');
		Foo* foo3 = new Foo('c');

		fooStarVector.PushBack(foo1);
		fooStarVector.PushBack(foo2);
		fooStarVector.PushBack(foo3);

		fooStarVector.Remove(foo1);
		fooStarVector.PushBack(foo1);
		TS_ASSERT_EQUALS(fooStarVector.Size(), 3);
		TS_ASSERT_EQUALS(fooStarVector.Back(), foo1);

		delete foo1;
		delete foo2;
		delete foo3;
	}

	void TestIndexing()
	{
		Vector<int*> intStarVector;

		//access empty vector
		TS_ASSERT_THROWS(intStarVector[1], std::out_of_range);

		int a = 10;
		int b = 20;
		int c = 30;
		intStarVector.PushBack(&a);
		intStarVector.PushBack(&b);
		intStarVector.PushBack(&c);

		//access present index
		TS_ASSERT_EQUALS(*intStarVector[2], 30);

		//access beyond bounds
		TS_ASSERT_THROWS(intStarVector[5], std::out_of_range);

		//modify using valid index
		*intStarVector[0] = 100;
		TS_ASSERT_EQUALS(*intStarVector.Front(), 100);

		//modifying using invalid index
		TS_ASSERT_THROWS(*intStarVector[5] = 10, std::out_of_range);
	}

	void TestEqualsOperator()
	{
		Vector<int> intVector;
		intVector.PushBack(1);
		intVector.PushBack(2);
		intVector.PushBack(3);

		Vector<int> anotherIntVector;
		anotherIntVector = intVector;

		int i = 0;
		for (auto value : anotherIntVector)
		{
			TS_ASSERT_EQUALS(value, ++i);
		}
	}

	void TestVectorCopyConstructor()
	{
		Vector<int> intVector;
		intVector.PushBack(1);
		intVector.PushBack(2);
		intVector.PushBack(3);

		Vector<int> anotherIntVector = intVector;

		int i = 0;
		for (auto value : anotherIntVector)
		{
			TS_ASSERT_EQUALS(value, ++i);
		}
	}

	void TestAt()
	{
		Vector<int> intVector;
		intVector.PushBack(1);
		intVector.PushBack(2);
		intVector.PushBack(3);

		TS_ASSERT_EQUALS(intVector.Capacity(), 4);

		//normal access
		TS_ASSERT_EQUALS(intVector.At(1), 2);

		//beyond size
		TS_ASSERT_EQUALS(intVector.At(3), 0);

		//beyond capacity
		TS_ASSERT_THROWS(intVector.At(10), std::out_of_range);
	}

	void TestIteratorCopyConstructor()
	{
		Vector<int> intVector;
		intVector.PushBack(1);
		intVector.PushBack(2);
		intVector.PushBack(3);

		Vector<int>::Iterator it = intVector.Find(1);

		TS_ASSERT_EQUALS(*it, 1);
		TS_ASSERT_EQUALS(it, intVector.begin());

		Vector<Foo> fooVector;
		Vector<Foo>::Iterator anotherIt = fooVector.begin();
		Vector<Foo>::Iterator yetAnotherIt = anotherIt; //copying empty iterator

		TS_ASSERT_THROWS((*yetAnotherIt).GetID(), std::out_of_range);
		TS_ASSERT_EQUALS(yetAnotherIt, fooVector.end());
	}

	void TestIteratorEqualsOperator()
	{
		Vector<int> intVector;
		intVector.PushBack(1);
		intVector.PushBack(2);
		intVector.PushBack(3);

		Vector<int>::Iterator it;
		it = intVector.Find(1);

		TS_ASSERT_EQUALS(*it, 1);
		TS_ASSERT_EQUALS(it, intVector.begin());

		Vector<Foo> fooVector;
		Vector<Foo>::Iterator anotherIt;
		anotherIt = fooVector.begin();

		Vector<Foo>::Iterator yetAnotherIt;
		yetAnotherIt = anotherIt;

		TS_ASSERT_THROWS((*yetAnotherIt).GetID(), std::out_of_range);
		TS_ASSERT_EQUALS(yetAnotherIt, fooVector.end());
	}

	void TestIteration()
	{
		Vector<int> intVector;
		intVector.PushBack(1);
		intVector.PushBack(2);
		intVector.PushBack(3);
		intVector.PushBack(4);
		intVector.PushBack(5);

		int i = 0;
		for (auto it = intVector.begin(); it != intVector.end(); ++it)
		{
			TS_ASSERT_EQUALS(*it, ++i);
		}

		TS_ASSERT_EQUALS(i, 5);
	}

	void TestIteratorEquality()
	{
		Vector<int> intVector;
		intVector.PushBack(1);
		intVector.PushBack(2);

		Vector<int> anotherIntVector;
		anotherIntVector.PushBack(1);
		TS_ASSERT(intVector.begin() == intVector.Find(1)); //same
		TS_ASSERT(intVector.begin() != intVector.Find(2)); //different index
		TS_ASSERT(intVector.Find(1) != anotherIntVector.Find(1)); //different owner
	}

	void TestIteratorPostIncrement()
	{
		Vector<int> intVector;
		intVector.PushBack(1);
		intVector.PushBack(2);

		Vector<int>::Iterator it = intVector.begin();
		Vector<int>::Iterator anotherIt = it++;

		TS_ASSERT_EQUALS(*it, 2);
		TS_ASSERT_EQUALS(*anotherIt, 1);
	}

	void TestIteratorSubtract()
	{
		Vector<Foo, FooFunctor> fooVector;

		Foo foo1('1');
		Foo foo2('2');
		Foo foo3('3');

		fooVector.PushBack(foo1);
		fooVector.PushBack(foo2);
		fooVector.PushBack(foo3);

		TS_ASSERT_EQUALS((fooVector.Find(foo3) - fooVector.Find(foo3)), 0);
		TS_ASSERT_EQUALS((fooVector.Find(foo3) - fooVector.Find(foo1)), 2);
		TS_ASSERT_EQUALS((fooVector.Find(foo1) - fooVector.Find(foo3)), -2);
	}
};
