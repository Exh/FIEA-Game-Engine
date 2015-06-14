#pragma once

#include <cxxtest/TestSuite.h>
#include "vld.h"

#include "pch.h"
#include "Datum.h"

#include "Foo.h"
#include "AnotherFoo.h"

using namespace Library;
using namespace Test;

class DatumTestSuite : public CxxTest::TestSuite
{
public:

	void TestConstructionDestruction()
	{
		//construction of internal datum
		Datum intDatum(Datum::DatumType::Integer, false,3);
		TS_ASSERT_EQUALS(intDatum.Size(), 3);
		TS_ASSERT_EQUALS(intDatum.Capacity(), 3);
		TS_ASSERT_EQUALS(intDatum.GetType(), Datum::DatumType::Integer);
		TS_ASSERT_EQUALS(intDatum.IsExternal(), false);

		//clear internal datum
		intDatum.Clear();
		TS_ASSERT_EQUALS(intDatum.Size(), 0);
		TS_ASSERT_EQUALS(intDatum.Capacity(), 3);
		TS_ASSERT_EQUALS(intDatum.GetType(), Datum::DatumType::Integer);
		TS_ASSERT_EQUALS(intDatum.IsExternal(), false);

		//construct external int datum
		Datum intDatum1(Datum::DatumType::Integer, true);
		TS_ASSERT_EQUALS(intDatum1.Size(), 0);
		TS_ASSERT_EQUALS(intDatum1.Capacity(), 0);
		TS_ASSERT_EQUALS(intDatum1.GetType(), Datum::DatumType::Integer);
		TS_ASSERT_EQUALS(intDatum1.IsExternal(), true);

		//clear external datum
		intDatum1.Clear();
		TS_ASSERT_EQUALS(intDatum1.Size(), 0);
		TS_ASSERT_EQUALS(intDatum1.Capacity(), 0);
		TS_ASSERT_EQUALS(intDatum1.GetType(), Datum::DatumType::Integer);
		TS_ASSERT_EQUALS(intDatum1.IsExternal(), true);

		//internal pointer datum
		Datum rd(Datum::DatumType::Pointer, false, 5);
		TS_ASSERT_EQUALS(rd.Size(), 5);
		TS_ASSERT_EQUALS(rd.Capacity(), 5);
		TS_ASSERT_EQUALS(rd.GetType(), Datum::DatumType::Pointer);
		TS_ASSERT_EQUALS(rd.IsExternal(), false);

		//clear internal pointer datum
		rd.Clear();
		TS_ASSERT_EQUALS(rd.Size(), 0);
		TS_ASSERT_EQUALS(rd.Capacity(), 5);
		TS_ASSERT_EQUALS(rd.GetType(), Datum::DatumType::Pointer);
		TS_ASSERT_EQUALS(rd.IsExternal(), false);
	}

	void TestSetType()
	{
		//internal int
		Datum intDatum;
		//type not set
		intDatum.SetType(Datum::DatumType::Integer);
		TS_ASSERT_EQUALS(intDatum.GetType(), Datum::DatumType::Integer);
		//set type again
		TS_ASSERT_THROWS(intDatum.SetType(Datum::DatumType::Float), std::exception);
		//set invalid
		TS_ASSERT_THROWS(intDatum.SetType(Datum::DatumType::Unknown), std::exception);

		//external int
		Datum intDatum1(Datum::DatumType::Unknown, true);
		intDatum1.SetType(Datum::DatumType::Integer);
		TS_ASSERT_EQUALS(intDatum1.GetType(), Datum::DatumType::Integer);
		TS_ASSERT_THROWS(intDatum1.SetType(Datum::DatumType::Float), std::exception);
		TS_ASSERT_THROWS(intDatum1.SetType(Datum::DatumType::Unknown), std::exception);

		//internal pointer
		Datum pDatum1(Datum::DatumType::Unknown);
		pDatum1.SetType(Datum::DatumType::Pointer);
		TS_ASSERT_EQUALS(pDatum1.GetType(), Datum::DatumType::Pointer);
		TS_ASSERT_THROWS(pDatum1.SetType(Datum::DatumType::Float), std::exception);
		TS_ASSERT_THROWS(pDatum1.SetType(Datum::DatumType::Unknown), std::exception);
	}

	void SetSize()
	{	
		Datum intDatum(Datum::DatumType::Integer, false, 3);
		//normal set size
		intDatum.SetSize(6);
		TS_ASSERT_EQUALS(intDatum.Size(), 6);
		TS_ASSERT_EQUALS(intDatum.Capacity(), 6);
		//set a lower size
		intDatum.SetSize(2);
		TS_ASSERT_EQUALS(intDatum.Size(), 2);
		TS_ASSERT_EQUALS(intDatum.Capacity(), 6);

		//set size on external
		Datum intDatum1(Datum::DatumType::Integer, true);
		TS_ASSERT_THROWS(intDatum1.SetSize(6), std::exception);
	}

	void TestSetGet()
	{
		//internal int datum
		Datum intDatum(Datum::DatumType::Unknown, false, 3);
		TS_ASSERT_EQUALS(intDatum.Size(), 0);
		TS_ASSERT_EQUALS(intDatum.Capacity(), 0);

		//set out of bounds
		intDatum.Set(10, 5);
		TS_ASSERT_EQUALS(intDatum.Size(), 6);
		TS_ASSERT_EQUALS(intDatum.Capacity(), 6);
		TS_ASSERT_EQUALS(intDatum.Get<std::int32_t>(5), 10);

		//set invalid type
		TS_ASSERT_THROWS(intDatum.Set("apple"), std::exception);
		
		//get out of bounds
		intDatum.SetSize(2);
		TS_ASSERT_THROWS(intDatum.Get<std::int32_t>(5), std::out_of_range);

		//external int datum
		Datum extIntDatum(Datum::DatumType::Unknown, true);

		//set out of bounds external
		TS_ASSERT_THROWS(extIntDatum.Set(10), std::out_of_range);
		TS_ASSERT_THROWS(extIntDatum.Get<std::int32_t>(), std::exception);

		//get with setting storage
		extIntDatum.SetType(Datum::DatumType::Integer);
		TS_ASSERT_THROWS(extIntDatum.Get<std::int32_t>(), std::out_of_range);
		//get invalid type
		TS_ASSERT_THROWS(extIntDatum.Get<std::string>(), std::exception);

		Foo foo;
		AnotherFoo aFoo;

		//scalar set
		Datum rttiDatum(Datum::DatumType::Pointer);
		rttiDatum.Set(&foo);

		//scalar get
		TS_ASSERT(!rttiDatum.GetPointer()->Is(aFoo.TypeIdInstance()));
		TS_ASSERT(rttiDatum.GetPointer()->Is(foo.TypeIdInstance()));

	}

	void TestSetStorage()
	{
		std::int32_t data[3] = { 1, 2, 3 };
		
		//set storage in internal datum
		Datum intDatum(Datum::DatumType::Integer, false, 3);
		TS_ASSERT_THROWS(intDatum.SetStorage(data, 3), std::exception);

		//datum type not set beforehand
		Datum extDatum(Datum::DatumType::Unknown, true);
		extDatum.SetStorage(data, 3);
		TS_ASSERT_EQUALS(extDatum.GetType(), Datum::DatumType::Integer);
		
		extDatum.Set(10);
		TS_ASSERT(data[0] == 10);

		//set storage of anothe data type
		float fData[2];
		TS_ASSERT_THROWS(extDatum.SetStorage(fData, 2), std::exception);
	}

	void TestScalarAssignment()
	{
		//convert from ranged to scalar
		Datum intFloatDatum(Datum::DatumType::Float, false,5);
		intFloatDatum = 2.0f;
		TS_ASSERT_EQUALS(intFloatDatum.Get<float>(), 2.0f);
		TS_ASSERT_EQUALS(intFloatDatum.Size(), 1);
		
		//invalid assignment
		TS_ASSERT_THROWS(intFloatDatum = "foo", std::exception);

		float values[5] = {1.0f,3.0f,5.0,7.0f,9.0f};

		//assignment wihtout setting storage
		Datum extFloatDatum(Datum::DatumType::Float, true);
		TS_ASSERT_THROWS(extFloatDatum = 2.0f, std::exception);
		
		extFloatDatum.SetStorage(values, 5);
		TS_ASSERT_EQUALS(extFloatDatum.Size(), 5);
		
		//ranged storage to scalar
		extFloatDatum = 2.0f;
		TS_ASSERT_EQUALS(extFloatDatum.Size(), 5);
		TS_ASSERT_EQUALS(extFloatDatum.Get<float>(), 2.0f);

		//invalid assignment
		TS_ASSERT_THROWS(extFloatDatum = "foo", std::exception);
	}

	void TestEquality()
	{
		Datum intSd(Datum::DatumType::String, false, 4);

		//compare different datum type, same size
		Datum intFd(Datum::DatumType::Float, false, 4);
		TS_ASSERT(intSd != intFd);

		//compare same type, same size
		Datum intFd1(Datum::DatumType::Float, false, 5);
		Datum intFd2(Datum::DatumType::Float, false, 5);
		TS_ASSERT(intFd != intFd1);
		TS_ASSERT(intFd2 == intFd1);
		
		std::string nos[5] = { "ichi", "ni", "san", "yon", "go" };
		std::string nos1[5] = { "ichi", "ni", "san", "yon", "roku" };

		Datum extSd1(Datum::DatumType::String, true);
		extSd1.SetStorage(nos, 5);

		Datum extSd2(Datum::DatumType::String, true);
		extSd2.SetStorage(nos1, 5);

		//different data
		TS_ASSERT(extSd1 != extSd2);

		//external vs external, same data
		extSd1.SetStorage(nos, 4);
		extSd2.SetStorage(nos1, 4);
		TS_ASSERT(extSd1 == extSd2);

		intSd.Set(nos[0], 0);
		intSd.Set(nos[1], 1);
		intSd.Set(nos[2], 2);
		intSd.Set(nos[3], 3);
		//internal vs external
		TS_ASSERT(intSd == extSd1);
		//external vs internal 
		TS_ASSERT(extSd2 == intSd);
		//self assignment, internal vs internal
		TS_ASSERT(intSd == intSd);

		//scalar equality and inequality
		//int
		Datum i;
		i = 5;
		TS_ASSERT(i == 5);
		TS_ASSERT(i != 10);

		//float
		Datum f;
		f = 2.2f;
		TS_ASSERT(f == 2.2f);
		TS_ASSERT(f != 10.0f);

		//vector
		glm::vec4 vec(10);
		Datum v;
		v = vec;
		TS_ASSERT(v == vec);
		TS_ASSERT(v != vec*vec);

		//matrix
		glm::mat4 mat(2);
		Datum m;
		m = mat;
		TS_ASSERT(m == mat);
		TS_ASSERT(m != mat*vec);

		//rtti
		Foo foo;
		AnotherFoo aFoo;
		Datum p;
		p = &foo;
		TS_ASSERT(p == &foo);
		TS_ASSERT(p != &aFoo);

		//string
		Datum s;
		s = "string";
		TS_ASSERT(s == "string");
		TS_ASSERT(s != "STRING");

		//comapre different datum type scalars
		TS_ASSERT(i != s);
	}

	void TestCopying_InternalToInternal()
	{
		Datum intD1(Datum::DatumType::Integer, false, 3);
		intD1.Set(10, 0);
		intD1.Set(20, 1);
		intD1.Set(30, 2);

		//assignment
		Datum intD2(Datum::DatumType::String,false,2);
		intD2 = intD1;
		intD2.Set(11);
		TS_ASSERT_EQUALS(intD2.Size(), intD1.Size());
		TS_ASSERT_EQUALS(intD2.Capacity(), intD1.Capacity());
		TS_ASSERT_EQUALS(intD2.GetType(), intD1.GetType());
		TS_ASSERT_DIFFERS(intD2.Get<std::int32_t>(), intD1.Get<std::int32_t>());
		TS_ASSERT_EQUALS(intD2.IsExternal(), intD1.IsExternal());

		//copy constructor
		Datum intD3(intD1);
		intD3.Set(12);
		TS_ASSERT_EQUALS(intD3.Size(), intD1.Size());
		TS_ASSERT_EQUALS(intD3.Capacity(), intD1.Capacity());
		TS_ASSERT_EQUALS(intD3.GetType(), intD1.GetType());
		TS_ASSERT_DIFFERS(intD3.Get<std::int32_t>(), intD1.Get<std::int32_t>());
		TS_ASSERT_EQUALS(intD3.IsExternal(), intD1.IsExternal());

		Foo foo;
		AnotherFoo aFoo;
		RTTI* pValues[2] = { &foo, &aFoo };
		Datum rDatum(Datum::DatumType::Pointer, false,2);
		rDatum.Set(pValues[0], 0);
		rDatum.Set(pValues[1], 1);

		//assignment
		Datum intRd1;
		intRd1 = rDatum;
		intRd1.Set(&aFoo);
		TS_ASSERT_EQUALS(intRd1.Size(), rDatum.Size());
		TS_ASSERT_EQUALS(intRd1.Capacity(), rDatum.Capacity());
		TS_ASSERT_EQUALS(intRd1.GetType(), rDatum.GetType());
		TS_ASSERT_DIFFERS(intRd1.GetPointer(), rDatum.GetPointer());
		TS_ASSERT_EQUALS(intRd1.IsExternal(), rDatum.IsExternal());

		//copy constructor
		Datum intRd2(rDatum);
		intRd2.Set(&foo, 1);
		TS_ASSERT_EQUALS(intRd2.Size(), rDatum.Size());
		TS_ASSERT_EQUALS(intRd2.Capacity(), rDatum.Capacity());
		TS_ASSERT_EQUALS(intRd2.GetType(), rDatum.GetType());
		TS_ASSERT_DIFFERS(intRd2.GetPointer(1), rDatum.GetPointer(1));
		TS_ASSERT_EQUALS(intRd2.IsExternal(), rDatum.IsExternal());

	}

	void TestCopying_InternalToExternal()
	{
		Datum intD1(Datum::DatumType::Integer, false, 3);
		intD1.Set(10, 0);
		intD1.Set(20, 1);
		intD1.Set(30, 2);

		//assignment
		Datum extD1(Datum::DatumType::Integer, true);
		extD1 = intD1;
		extD1.Set(11);
		TS_ASSERT_EQUALS(extD1.Size(), intD1.Size());
		TS_ASSERT_EQUALS(extD1.Capacity(), intD1.Capacity());
		TS_ASSERT_EQUALS(extD1.GetType(), intD1.GetType());
		TS_ASSERT_DIFFERS(extD1.Get<std::int32_t>(), intD1.Get<std::int32_t>());
		TS_ASSERT_EQUALS(extD1.IsExternal(), intD1.IsExternal());

		Foo foo;
		AnotherFoo aFoo;
		RTTI* pValues[2] = { &foo, &aFoo };
		Datum rDatum(Datum::DatumType::Pointer, false, 2);
		rDatum.Set(pValues[0], 0);
		rDatum.Set(pValues[1], 1);

		//assignment
		Datum intRd1(Datum::DatumType::Vector, true);
		intRd1 = rDatum;
		intRd1.Set(&aFoo);
		TS_ASSERT_EQUALS(intRd1.Size(), rDatum.Size());
		TS_ASSERT_EQUALS(intRd1.Capacity(), rDatum.Capacity());
		TS_ASSERT_EQUALS(intRd1.GetType(), rDatum.GetType());
		TS_ASSERT_DIFFERS(intRd1.GetPointer(), rDatum.GetPointer());
		TS_ASSERT_EQUALS(intRd1.IsExternal(), rDatum.IsExternal());
	}

	void TestCopying_ExternalToInternal()
	{
		int values[4] = { 2, 3, 5, 7 };
		Datum extDatum(Datum::DatumType::Integer, true);
		extDatum.SetStorage(values, 4);

		//assignment
		Datum intDatum1(Datum::DatumType::Vector, false,5);
		intDatum1 = extDatum;
		intDatum1 = 1;
		TS_ASSERT_EQUALS(extDatum.Size(), intDatum1.Size());
		TS_ASSERT_EQUALS(extDatum.Capacity(), intDatum1.Capacity());
		TS_ASSERT_EQUALS(extDatum.GetType(), intDatum1.GetType());
		TS_ASSERT_EQUALS(extDatum.Get<std::int32_t>(), intDatum1.Get<std::int32_t>());
		TS_ASSERT_EQUALS(extDatum.IsExternal(), intDatum1.IsExternal());

		//copy constructor
		Datum intDatum2(extDatum);
		intDatum2 = 1;
		TS_ASSERT_EQUALS(extDatum.Size(), intDatum2.Size());
		TS_ASSERT_EQUALS(extDatum.Capacity(), intDatum2.Capacity());
		TS_ASSERT_EQUALS(extDatum.GetType(), intDatum2.GetType());
		TS_ASSERT_EQUALS(extDatum.Get<std::int32_t>(), intDatum2.Get<std::int32_t>());
		TS_ASSERT_EQUALS(extDatum.IsExternal(), intDatum2.IsExternal());

		Foo foo;
		AnotherFoo aFoo;
		RTTI* pValues[2] = { &foo, &aFoo };
		Datum rDatum(Datum::DatumType::Pointer, true);
		rDatum.SetStorage(pValues, 2);

		//assignment
		Datum intRd1;
		intRd1 = rDatum;
		intRd1.Set(&aFoo);
		TS_ASSERT_EQUALS(intRd1.Size(), rDatum.Size());
		TS_ASSERT_EQUALS(intRd1.Capacity(), rDatum.Capacity());
		TS_ASSERT_EQUALS(intRd1.GetType(), rDatum.GetType());
		TS_ASSERT_EQUALS(intRd1.GetPointer(), rDatum.GetPointer());
		TS_ASSERT_EQUALS(intRd1.IsExternal(), rDatum.IsExternal());

		//copy constructor
		Datum intRd2(rDatum);
		intRd2.Set(&foo, 1);
		TS_ASSERT_EQUALS(intRd2.Size(), rDatum.Size());
		TS_ASSERT_EQUALS(intRd2.Capacity(), rDatum.Capacity());
		TS_ASSERT_EQUALS(intRd2.GetType(), rDatum.GetType());
		TS_ASSERT_EQUALS(intRd2.GetPointer(1), rDatum.GetPointer(1));
		TS_ASSERT_EQUALS(intRd2.IsExternal(), rDatum.IsExternal());
	}

	void TestCopying_ExternalToExternal()
	{
		int values[4] = { 2, 3, 5, 7 };
		Datum extDatum(Datum::DatumType::Integer, true);
		extDatum.SetStorage(values, 4);

		//assignment
		Datum extDatum1(Datum::DatumType::Vector, true, 5);
		extDatum1 = extDatum;
		extDatum1 = 1;
		TS_ASSERT_EQUALS(extDatum.Size(), extDatum1.Size());
		TS_ASSERT_EQUALS(extDatum.Capacity(), extDatum1.Capacity());
		TS_ASSERT_EQUALS(extDatum.GetType(), extDatum1.GetType());
		TS_ASSERT_EQUALS(extDatum.Get<std::int32_t>(), extDatum1.Get<std::int32_t>());
		TS_ASSERT_EQUALS(extDatum.IsExternal(), extDatum1.IsExternal());
	
		Foo foo;
		AnotherFoo aFoo;
		RTTI* pValues[2] = { &foo, &aFoo };
		Datum rDatum(Datum::DatumType::Pointer, true);
		rDatum.SetStorage(pValues, 2);

		//assignment
		Datum intRd1(Datum::DatumType::Matrix,true);
		intRd1 = rDatum;
		intRd1.Set(&aFoo);
		TS_ASSERT_EQUALS(intRd1.Size(), rDatum.Size());
		TS_ASSERT_EQUALS(intRd1.Capacity(), rDatum.Capacity());
		TS_ASSERT_EQUALS(intRd1.GetType(), rDatum.GetType());
		TS_ASSERT_EQUALS(intRd1.GetPointer(), rDatum.GetPointer());
		TS_ASSERT_EQUALS(intRd1.IsExternal(), rDatum.IsExternal());
	}

	void TestStringParsing()
	{
		Datum intDatum(Datum::DatumType::Integer);
		intDatum = 100;
		//normal
		intDatum.SetFromString(intDatum.ToString());
		TS_ASSERT_EQUALS(intDatum, 100);

		//invalid format
		TS_ASSERT_THROWS(intDatum.SetFromString("funky"), std::exception);
		TS_ASSERT_THROWS(intDatum.TrySetFromString("funky",0,true), std::exception);

		//setting default silently on failure
		TS_ASSERT_THROWS_NOTHING(intDatum.TrySetFromString("funky"));
		TS_ASSERT_EQUALS(intDatum, 0);

		//same for float
		Datum fDatum(Datum::DatumType::Float);
		fDatum = 3.142f;
		fDatum.SetFromString(fDatum.ToString());
		TS_ASSERT_EQUALS(fDatum, 3.142f);

		TS_ASSERT_THROWS(fDatum.TrySetFromString("funky", 0, true), std::exception);
		TS_ASSERT_THROWS_NOTHING(fDatum.TrySetFromString("funky"));
		TS_ASSERT_EQUALS(fDatum, 0.0f);

		//and vectors
		glm::vec4 vec(1.5f);
		Datum vecDatum(Datum::DatumType::Vector);
		vecDatum=vec;
		vecDatum.SetFromString(vecDatum.ToString());
		TS_ASSERT_EQUALS(vecDatum, vec);

		//insufficient data
		TS_ASSERT_THROWS_NOTHING(vecDatum.SetFromString("(0.1, 0.1)"));

		TS_ASSERT_THROWS(vecDatum.TrySetFromString("funky", 0, true), std::exception);
		TS_ASSERT_THROWS_NOTHING(vecDatum.TrySetFromString("funky"));
		TS_ASSERT_EQUALS(vecDatum, glm::vec4(0));

		//and matrix
		glm::mat4 mat(22);
		Datum matDatum(Datum::DatumType::Matrix);
		matDatum = mat;
		matDatum.SetFromString(matDatum.ToString());
		TS_ASSERT_EQUALS(matDatum, mat);

		//insufficient data
		TS_ASSERT_THROWS_NOTHING(matDatum.SetFromString("((0.1, 0.1))"));

		TS_ASSERT_THROWS(matDatum.TrySetFromString("funky", 0, true), std::exception);
		TS_ASSERT_THROWS_NOTHING(matDatum.TrySetFromString("funky"));
		TS_ASSERT_EQUALS(matDatum, glm::mat4(0));

		//string
		Datum strDatum(Datum::DatumType::String);
		strDatum = "apple";
		strDatum.SetFromString(strDatum.ToString());
		TS_ASSERT_EQUALS(strDatum, "apple");

		TS_ASSERT_THROWS_NOTHING(strDatum.TrySetFromString("funky", 0, true));
		TS_ASSERT_EQUALS(strDatum, "funky");
		TS_ASSERT_THROWS_NOTHING(strDatum.TrySetFromString("funky apple"));
		TS_ASSERT_EQUALS(strDatum, "funky apple");

		//pointers
		Datum rttiDatum(Datum::DatumType::Pointer);
		TS_ASSERT_THROWS(rttiDatum.SetFromString(rttiDatum.ToString()), std::exception);
	}
};