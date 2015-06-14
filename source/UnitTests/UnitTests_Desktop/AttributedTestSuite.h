#pragma once

#include <cxxtest/TestSuite.h>
#include "vld.h"

#include "pch.h"
#include "ScalarAttributedFoo.h"
#include "VectorAttributedFoo.h"

using namespace Library;
using namespace Test;

class AttributedTestSuite : public CxxTest::TestSuite
{
public:
	void TestConstruction()
	{
		ScalarAttributedFoo scalarFoo;
		TS_ASSERT(scalarFoo.Size() != 0);
		//TS_ASSERT_EQUALS(Attributed::sSignatures.Size(), 1);
		//TS_ASSERT_EQUALS(scalarFoo.mSignatures.Size(), 1);
		TS_ASSERT_EQUALS(scalarFoo.AuxiliaryBegin(), scalarFoo.Size());
		
		//test this
		TS_ASSERT(scalarFoo["this"]== &scalarFoo);
		TS_ASSERT_EQUALS(scalarFoo[0], &scalarFoo);

		VectorAttributedFoo vectorFoo;
		TS_ASSERT(vectorFoo.Size() != 0);
		//TS_ASSERT_EQUALS(Attributed::sSignatures.Size(), 2);
		TS_ASSERT_EQUALS(vectorFoo.AuxiliaryBegin(), vectorFoo.Size());

		//test this
		TS_ASSERT_EQUALS(vectorFoo["this"], &vectorFoo);
		TS_ASSERT_EQUALS(vectorFoo[0], &vectorFoo);

		//test that we dont add another set of signatures with another instance
		ScalarAttributedFoo scalarFoo2;
		//TS_ASSERT_EQUALS(Attributed::sSignatures.Size(), 2);
	}

	void TestCopying()
	{
		ScalarAttributedFoo scalarFoo;
		scalarFoo.AppendAuxiliaryAttribute("name") = 10;

		//operator =
		ScalarAttributedFoo scalarFoo1;
		scalarFoo1 = scalarFoo;
		TS_ASSERT_EQUALS(scalarFoo1.Size(), scalarFoo.Size());
		TS_ASSERT_EQUALS(scalarFoo1["Ext int"], scalarFoo["Ext int"]);
		TS_ASSERT_EQUALS(scalarFoo1["name"], scalarFoo["name"]);
		TS_ASSERT_DIFFERS(scalarFoo1["this"], scalarFoo["this"]);

		//copy constructor
		ScalarAttributedFoo scalarFoo2(scalarFoo);
		TS_ASSERT_EQUALS(scalarFoo2.Size(), scalarFoo.Size());
		TS_ASSERT_EQUALS(scalarFoo2["Ext int"], scalarFoo["Ext int"]);
		TS_ASSERT_EQUALS(scalarFoo2["name"], scalarFoo["name"]);
		TS_ASSERT_DIFFERS(scalarFoo2["this"], scalarFoo["this"]);

		VectorAttributedFoo vectorFoo;

		//operator =
		VectorAttributedFoo vectorFoo1;
		vectorFoo1 = vectorFoo;
		TS_ASSERT_EQUALS(vectorFoo1.Size(), vectorFoo.Size());
		TS_ASSERT_EQUALS(vectorFoo1["Ext int"], vectorFoo["Ext int"]);
		TS_ASSERT_EQUALS(vectorFoo1["name"], vectorFoo["name"]);
		TS_ASSERT_DIFFERS(vectorFoo1["this"], vectorFoo["this"]);

		//copy constructor
		VectorAttributedFoo vectorFoo2(vectorFoo);
		TS_ASSERT_EQUALS(vectorFoo2.Size(), vectorFoo.Size());
		TS_ASSERT_EQUALS(vectorFoo2["Ext int"], vectorFoo["Ext int"]);
		TS_ASSERT_EQUALS(vectorFoo2["name"], vectorFoo["name"]);
		TS_ASSERT_DIFFERS(vectorFoo2["this"], vectorFoo["this"]);
	}

	void TestIsPrescribedAttribute()
	{
		ScalarAttributedFoo scalarFoo;
		//attribute not prescribed
		TS_ASSERT(scalarFoo.IsPrescribedAttribute("name") == false);
		//prescribed external
		TS_ASSERT(scalarFoo.IsPrescribedAttribute("Ext mat4"));
		//prescribed internal
		TS_ASSERT(scalarFoo.IsPrescribedAttribute("Int rtti"));
		//this
		TS_ASSERT(scalarFoo.IsPrescribedAttribute("this") == false);

		//same for vector foo
		VectorAttributedFoo vectorFoo;
		TS_ASSERT(vectorFoo.IsPrescribedAttribute("name") == false);
		TS_ASSERT(vectorFoo.IsPrescribedAttribute("Ext mat4"));
		TS_ASSERT(vectorFoo.IsPrescribedAttribute("Int rtti"));
		TS_ASSERT(vectorFoo.IsPrescribedAttribute("this") == false);
	}

	void TestIsAuxiliaryAttribute()
	{
		ScalarAttributedFoo scalarFoo;
		//attribute that is not present
		TS_ASSERT(scalarFoo.IsAuxiliaryAttribute("name") == false);
		//this attribute
		TS_ASSERT(scalarFoo.IsAuxiliaryAttribute("this"));
		//prescribed attribute
		TS_ASSERT(scalarFoo.IsAuxiliaryAttribute("Ext int") == false);

		//same for vector foo
		VectorAttributedFoo vectorFoo;
		//attribute that is not present
		TS_ASSERT(vectorFoo.IsAuxiliaryAttribute("name") == false);
		//this attribute
		TS_ASSERT(vectorFoo.IsAuxiliaryAttribute("this"));
		//prescribed attribute
		TS_ASSERT(vectorFoo.IsAuxiliaryAttribute("Ext int") == false);
	}

	void TestIsAttribute()
	{
		ScalarAttributedFoo scalarFoo;
		//attribute not present
		TS_ASSERT(scalarFoo.IsAttribute("hello") == false);

		//prescribed attribute
		TS_ASSERT(scalarFoo.IsAttribute("Ext int"));

		//auxiliary attribute
		TS_ASSERT(scalarFoo.IsAttribute("this"));

		//same for vector foo
		VectorAttributedFoo vectorFoo;
		//attribute not present
		TS_ASSERT(vectorFoo.IsAttribute("hello") == false);

		//prescribed attribute
		TS_ASSERT(vectorFoo.IsAttribute("Ext int"));

		//auxiliary attribute
		TS_ASSERT(vectorFoo.IsAttribute("this"));
	}

	void TestAppendAuxiliary()
	{
		ScalarAttributedFoo scalarFoo;
		//appending prescribed
		TS_ASSERT_THROWS(scalarFoo.AppendAuxiliaryAttribute("Ext string"), std::exception);

		//appending this
		TS_ASSERT_THROWS(scalarFoo.AppendAuxiliaryAttribute("this"), std::exception);

		//appending new attribute
		std::uint32_t oldSize = scalarFoo.Size();
		scalarFoo.AppendAuxiliaryAttribute("name");
		TS_ASSERT(scalarFoo.IsAuxiliaryAttribute("name"));
		TS_ASSERT(scalarFoo.IsPrescribedAttribute("name")==false);
		TS_ASSERT_EQUALS(scalarFoo.Size(), oldSize + 1);

		//same for vector foo
		VectorAttributedFoo vectorFoo;

		//appending prescribed
		TS_ASSERT_THROWS(vectorFoo.AppendAuxiliaryAttribute("Ext string"), std::exception);

		//appending this
		TS_ASSERT_THROWS(vectorFoo.AppendAuxiliaryAttribute("this"), std::exception);

		//appending new attribute
		oldSize = vectorFoo.Size();
		vectorFoo.AppendAuxiliaryAttribute("name");
		TS_ASSERT(vectorFoo.IsAuxiliaryAttribute("name"));
		TS_ASSERT(vectorFoo.IsPrescribedAttribute("name") == false);
		TS_ASSERT_EQUALS(vectorFoo.Size(), oldSize + 1);
	}

	void TestModifyingValues()
	{
		ScalarAttributedFoo scalarFoo;
		//modify external
		scalarFoo.mExtInt = 10;
		scalarFoo["Ext int"] = 20;
		TS_ASSERT_EQUALS(scalarFoo.mExtInt, 20);
		
		//modify internal
		scalarFoo["Int int"] = 20;
		TS_ASSERT_EQUALS(scalarFoo["Int int"], 20);

		VectorAttributedFoo vectorFoo;
		//modify external
		vectorFoo.mExtInt[1] = 10;
		vectorFoo["Ext int"].Get<std::int32_t>(1) = 20;
		TS_ASSERT_EQUALS(vectorFoo.mExtInt[1], 20);

		//modify internal
		vectorFoo["Int int"].Get<std::int32_t>(0) = 10;
		TS_ASSERT_EQUALS(vectorFoo["Int int"], 10);
	}

	void TestEquality()
	{
		ScalarAttributedFoo scalarFoo1;
		ScalarAttributedFoo scalarFoo2;

		ScalarAttributedFoo scalarFoo3;
		scalarFoo3.AppendAuxiliaryAttribute("name");
		
		ScalarAttributedFoo scalarFoo4;
		scalarFoo4["Int int"] = 100;

		//same
		TS_ASSERT(scalarFoo1 == scalarFoo2);
		//different
		TS_ASSERT(scalarFoo1 != scalarFoo3);
		//same structure but  different values
		TS_ASSERT(scalarFoo1 != scalarFoo4);
		//self equality
		TS_ASSERT(scalarFoo1 == scalarFoo1);

		//same for vector
		VectorAttributedFoo vectorFoo1;
		VectorAttributedFoo vectorFoo2;

		VectorAttributedFoo vectorFoo3;
		vectorFoo3.AppendAuxiliaryAttribute("name");

		VectorAttributedFoo vectorFoo4;
		vectorFoo4["Int int"] = 100;

		TS_ASSERT(vectorFoo1 == vectorFoo2);
		TS_ASSERT(vectorFoo1 != vectorFoo3);
		TS_ASSERT(vectorFoo1 != vectorFoo4);
		TS_ASSERT(vectorFoo1 == vectorFoo1);
	}
};