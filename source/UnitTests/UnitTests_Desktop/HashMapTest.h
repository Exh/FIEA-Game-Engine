#pragma once

#include <string>
#include <cxxtest/TestSuite.h>
#include "vld.h"

#include "hashmap.h"
#include "Foo.h"
#include "FooHash.h"

using namespace Library;
using namespace Test;

class HashMapTestSuite : public CxxTest::TestSuite
{
public:

	void TestInsert()
	{
		//inserting with the same key
		HashMap<int, std::string> intStringMap = HashMap<int, std::string>();
		TS_ASSERT_EQUALS(intStringMap.Size(), 0);
		intStringMap.Insert(1, "apple");
		intStringMap.Insert(1, "pear");
		TS_ASSERT_EQUALS(intStringMap.Size(), 1);

		//normal insert
		Foo foo('1');
		HashMap<Foo, float, FooHash> fooFloatMap = HashMap<Foo, float, FooHash>();
		TS_ASSERT_EQUALS(fooFloatMap.Size(), 0);
		fooFloatMap.Insert(foo, 0.5);
		TS_ASSERT_EQUALS(fooFloatMap.Size(), 1);

		//insert as a pair
		int a = 10;
		int b = 20;
		HashMap<int*, char> intStarCharMap = HashMap<int*, char>();
		TS_ASSERT_EQUALS(intStarCharMap.Size(), 0);
		intStarCharMap.Insert(std::pair<int*, char>(&a, 'a'));
		intStarCharMap.Insert(std::pair<int*, char>(&b, 'b'));
		TS_ASSERT_EQUALS(intStarCharMap.Size(), 2);

		//normal insert again
		HashMap<std::string, Foo> stringFooMap = HashMap<std::string, Foo>();
		TS_ASSERT_EQUALS(stringFooMap.Size(), 0);
		stringFooMap.Insert("alice", foo);
	}

	void TestClear()
	{
		//clearing with data
		HashMap<int, std::string> intStringMap = HashMap<int, std::string>();
		TS_ASSERT_EQUALS(intStringMap.Size(), 0);
		intStringMap.Insert(1, "apple");
		intStringMap.Insert(2, "pear");
		intStringMap.Clear();
		TS_ASSERT_EQUALS(intStringMap.Size(), 0);

		//clearing empty
		Foo foo('1');
		HashMap<Foo, float, FooHash> fooFloatMap = HashMap<Foo, float, FooHash>();
		fooFloatMap.Clear();
		TS_ASSERT_EQUALS(fooFloatMap.Size(), 0);
	}

	void TestIndex()
	{
		HashMap<int, std::string> intStringMap = HashMap<int, std::string>();
		TS_ASSERT_EQUALS(intStringMap.Size(), 0);
		intStringMap.Insert(1, "apple");
		intStringMap.Insert(2, "pear");

		//[] on rhs with existing key
		TS_ASSERT_EQUALS(intStringMap[1], "apple");

		//[] on rhs with non-existing key
		TS_ASSERT_EQUALS(intStringMap[3], "");

		//[] on lhs with existing key
		intStringMap[1] = "duck";
		TS_ASSERT_EQUALS(intStringMap[1], "duck");

		//[] on lhs with non-existing key
		intStringMap[4] = "bear";
		TS_ASSERT_EQUALS(intStringMap[4], "bear");
	}

	void TestRemove()
	{
		//normal types
		HashMap<std::string, bool> propertyTable = HashMap<std::string, bool>();
		propertyTable["transform"] = true;
		propertyTable["mesh"] = true;
		propertyTable["point light"] = false;
		TS_ASSERT_EQUALS(propertyTable.Size(), 3);

		//remove found
		propertyTable.Remove("point light");
		TS_ASSERT_EQUALS(propertyTable.Size(), 2);
		TS_ASSERT(propertyTable.Find("point light") == propertyTable.end());

		//remove not found
		propertyTable.Remove("audio clip");
		TS_ASSERT_EQUALS(propertyTable.Size(), 2);
		TS_ASSERT(propertyTable.Find("audio clip") == propertyTable.end());


		//pointer types
		Foo* foo1 = new Foo('1');
		Foo* foo2 = new Foo('2');
		HashMap<Foo*, int> fooStarMap = HashMap<Foo*, int>();
		fooStarMap[foo1] = 10;

		fooStarMap.Remove(foo1);
		TS_ASSERT_EQUALS(fooStarMap.Size(), 0);
		TS_ASSERT(fooStarMap.Find(foo1) == fooStarMap.end());

		fooStarMap.Remove(foo2);
		TS_ASSERT_EQUALS(fooStarMap.Size(), 0);
		TS_ASSERT(fooStarMap.Find(foo2) == fooStarMap.end());

		fooStarMap.Clear();
		delete foo1;
		delete foo2;
	}

	void TestFind()
	{
		HashMap<std::string, int> sizeTable = HashMap<std::string, int>();
		sizeTable["int"] = sizeof(int);
		sizeTable["char"] = sizeof(char);
		sizeTable["Foo"] = sizeof(Foo);

		//find found
		auto it = sizeTable.Find("char");
		TS_ASSERT_DIFFERS(it, sizeTable.end());

		//find not found
		auto it1 = sizeTable.Find("float");
		TS_ASSERT(it1==sizeTable.end());
	}

	void TestContainsKey()
	{
		char* place1 = "Japan";
		char* place2 = "America";

		HashMap<char*, std::string> geographyMap = HashMap<char*, std::string>();
		geographyMap.Insert(place1, "Tokyo");

		//key found
		TS_ASSERT(geographyMap.ContainsKey(place1));

		//key not found
		TS_ASSERT(!geographyMap.ContainsKey(place2));
	}

	void TestRehashing()
	{
		HashMap<int, int> squaresTable = HashMap<int, int>();
		squaresTable[1] = 1;
		squaresTable[2] = 4;
		squaresTable[3] = 9;
		
		float oldLoadFactor = squaresTable.GetLoadFactor();

		squaresTable.RehashTable();

		TS_ASSERT_EQUALS(squaresTable.Size(), 3);
		TS_ASSERT_EQUALS(squaresTable[1], 1);
		TS_ASSERT_EQUALS(squaresTable[2], 4);
		TS_ASSERT_EQUALS(squaresTable[3], 9);
		TS_ASSERT(squaresTable.GetLoadFactor()<oldLoadFactor);
	}

	void TestIterator()
	{
		HashMap<int, std::string,FooHash> studentsMap = HashMap<int, std::string,FooHash>(2);
		studentsMap[100] = "Harry";
		studentsMap[101] = "Barry";
		studentsMap[102] = "Perry";
		
		auto it1 = studentsMap.Find(100);
		auto it2 = studentsMap.Find(101);
		auto it3 = studentsMap.Find(102);

		HashMap<int, std::string, FooHash> anotherMap = studentsMap;
		anotherMap[100] = "Cherry";

		auto it4 = anotherMap.Find(100);

		//owners dont match
		TS_ASSERT_DIFFERS(it1, it4);

		//buckets dont match
		TS_ASSERT_DIFFERS(it1, it3);

		//chains dont match
		TS_ASSERT_DIFFERS(it1, it2);

		//comparison to itself
		TS_ASSERT_EQUALS(it4, it4);

		//incrementing an invalid iterator
		auto it5 = studentsMap.Find(1000);
		TS_ASSERT_THROWS(it5++, std::out_of_range);
		TS_ASSERT_THROWS(++it5, std::out_of_range);

		//dereferencing an invalid iterator
		HashMap<int, std::string, FooHash>::Iterator it6;
		TS_ASSERT_THROWS(*it6, std::exception);
	}

	void TestCopying()
	{
		HashMap<int, std::string> intStringMap = HashMap<int, std::string>();
		intStringMap.Insert(1, "apple");
		intStringMap.Insert(2, "pear");

		//copy constructor
		HashMap<int, std::string> anotherMap(intStringMap);
		TS_ASSERT_EQUALS(anotherMap.Size(), intStringMap.Size());
		TS_ASSERT_EQUALS(anotherMap[1], intStringMap[1]);
		TS_ASSERT_EQUALS(anotherMap[2], intStringMap[2]);

		//= operator
		HashMap<int, std::string> yetAnotherMap;
		yetAnotherMap = intStringMap;
		TS_ASSERT_EQUALS(yetAnotherMap.Size(), intStringMap.Size());
		TS_ASSERT_EQUALS(yetAnotherMap[1], intStringMap[1]);
		TS_ASSERT_EQUALS(yetAnotherMap[2], intStringMap[2]);

		//same with pointer types
		Foo* foo1 = new Foo('1');
		Foo* foo2 = new Foo('2');
		HashMap<Foo*, int> fooStarMap = HashMap<Foo*, int>();
		fooStarMap[foo1] = 10;
		fooStarMap[foo2] = 20;

		HashMap<Foo*, int> anotherFooStarMap = fooStarMap;
		TS_ASSERT_EQUALS(anotherFooStarMap.Size(), fooStarMap.Size());
		TS_ASSERT_EQUALS(anotherFooStarMap[foo1], fooStarMap[foo1]);
		TS_ASSERT_EQUALS(anotherFooStarMap[foo2], fooStarMap[foo2]);

		HashMap<Foo*, int> yetAnotherFooStarMap;
		yetAnotherFooStarMap = fooStarMap;
		TS_ASSERT_EQUALS(yetAnotherFooStarMap.Size(), fooStarMap.Size());
		TS_ASSERT_EQUALS(yetAnotherFooStarMap[foo1], fooStarMap[foo1]);
		TS_ASSERT_EQUALS(yetAnotherFooStarMap[foo2], fooStarMap[foo2]);

		fooStarMap.Clear();
		anotherFooStarMap.Clear();
		yetAnotherFooStarMap.Clear();

		delete foo1;
		delete foo2;
	}
};