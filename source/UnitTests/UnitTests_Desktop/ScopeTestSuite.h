#pragma once

#include <cxxtest/TestSuite.h>
#include "vld.h"

#include "pch.h"

using namespace Library;

class ScopeTestSuite : public CxxTest::TestSuite
{
public:
	void TestConstructionDestruction()
	{
		Scope scope;
		TS_ASSERT(scope.Size() == 0);
	}

	void TestCopying()
	{
		Scope grandpa;
		grandpa.Append("name");

		Scope dad;
		dad.Append("address");
		grandpa.Adopt(dad, "1st gen");

		Scope son;
		son.Append("zipcode");
		dad.Adopt(son, "2nd gen");

		//copy entire hierarchy
		Scope grandpaCopy(grandpa);
		TS_ASSERT(grandpa == grandpaCopy);

		//copy just one
		Scope sonCopy = son;
		TS_ASSERT(sonCopy == son);

		//copy with several scopes in one level
		Scope daughter;
		dad.Adopt(daughter, "2nd gen");

		Scope grandDaughter;
		grandDaughter["name"] = "paula";
		daughter.Adopt(grandDaughter, "3rd gen");

		Scope grandkidCopy = grandDaughter;
		TS_ASSERT(grandkidCopy == grandDaughter);

		//modify and ensure it is a deep copy
		grandkidCopy["name"] = "aluap";
		TS_ASSERT(grandkidCopy != grandDaughter);
	}

	void TestFind()
	{
		Scope scope;
		scope.Append("id");
		scope.Append("name");
		TS_ASSERT(scope.Size() == 2);

		//find existing
		Datum* datum1 = scope.Find("name");
		TS_ASSERT(datum1 != nullptr);

		datum1 = scope.Find("id");
		TS_ASSERT(datum1 != nullptr);

		//find non existing
		datum1 = scope.Find("title");
		TS_ASSERT(datum1 == nullptr);

		//find with empty name
		datum1 = scope.Find("");
		TS_ASSERT(datum1 == nullptr);
	}

	void TestSearch()
	{
		Scope grandpa;
		grandpa.Append("name");

		Scope dad;
		dad.Append("address");
		grandpa.Adopt(dad, "1st gen");

		Scope son;
		son.Append("zipcode");
		dad.Adopt(son, "2nd gen");

		TS_ASSERT_EQUALS(grandpa.Size(), 2);
		TS_ASSERT_EQUALS(dad.Size(), 2);
		TS_ASSERT_EQUALS(son.Size(), 1);

		//find in current scope
		Scope* foundScope;
		Datum* foundDatum = son.Search("zipcode", &foundScope);
		TS_ASSERT_EQUALS(foundScope, &son);
		TS_ASSERT_DIFFERS(foundDatum, nullptr);

		//find in parent scope
		foundDatum = son.Search("address", &foundScope);
		TS_ASSERT_EQUALS(foundScope, &dad);
		TS_ASSERT_DIFFERS(foundDatum, nullptr);

		//find in grandparent scope
		foundDatum = son.Search("name", &foundScope);
		TS_ASSERT_EQUALS(foundScope, &grandpa);
		TS_ASSERT_DIFFERS(foundDatum, nullptr);

		//not found in any
		foundDatum = son.Search("state", &foundScope);
		TS_ASSERT_EQUALS(foundScope, nullptr);
		TS_ASSERT_EQUALS(foundDatum, nullptr);
	}

	void TestAppend()
	{
		Scope s;

		//append non existing datum 
		Datum& d1 = s.Append("name");
		d1 = "madeline";
		TS_ASSERT_EQUALS(s.Size(), 1);

		//append with datum type mismatch
		Datum& d2 = s["name"];
		TS_ASSERT_THROWS(d2 = 1, std::exception);

		//append to existing datum
		d2.Set("yumi", 1);
		TS_ASSERT_EQUALS(s.Size(), 1);
		TS_ASSERT_EQUALS(d2.Size(), 2);

		//append to external datum
		Datum& d3 = s.Append("ext");
		int age[2] = { 10, 12 };
		d3.SetStorage(age, 2);
		TS_ASSERT_THROWS(d3.Set(13, 3), std::exception);

		//insert with ""
		TS_ASSERT_THROWS(s.Append(""), std::exception);
	}

	void TestAppendScope()
	{
		Scope s;

		//append non existing
		s.AppendScope("position");
		TS_ASSERT_EQUALS(s.Size(), 1);

		//append to non table datum
		Datum& d1 = s.Append("rotation");
		d1.SetType(Datum::DatumType::Integer);
		TS_ASSERT_THROWS(s.AppendScope("rotation"), std::exception);

		//append to existing datum
		s.AppendScope("position");
		TS_ASSERT_EQUALS(s.Size(), 2);

		//insert with ""
		TS_ASSERT_THROWS(s.AppendScope(""), std::exception);
	}

	void TestAdopt()
	{
		Scope parent;
		Scope* child = parent.AppendScope("id");
		parent.AppendScope("name");

		//adopt to existing datum
		parent.Adopt(*child, "name");

		std::string name;
		TS_ASSERT(parent.FindName(*child, name));
		TS_ASSERT_EQUALS(name, "name");
		TS_ASSERT_EQUALS(parent.Size(), 2);

		Scope anotherChild;
		parent.Adopt(anotherChild, "name");
		TS_ASSERT_EQUALS(parent.Size(), 2);
		TS_ASSERT_EQUALS(parent.Find("name")->Size(),3);

		//adopt to new datum
		parent.Adopt(*child, "new");
		TS_ASSERT(parent.FindName(*child, name));
		TS_ASSERT_EQUALS(name, "new");

		//adopt at index
		parent.Adopt(*child, "id", 2);
		TS_ASSERT(parent.FindName(*child, name));
		TS_ASSERT_EQUALS(name, "id");

		//adopt null child
		//TS_ASSERT_THROWS(parent.Adopt(nullptr, "id", 2), std::exception);
	}

	void TestBracket()
	{
		Scope s1;
		s1["id"] = 1;

		//access existing
		TS_ASSERT_THROWS_NOTHING(s1[0] = 2);

		//access out of bounds
		TS_ASSERT_THROWS(s1[1] = 2, std::out_of_range);
	}

	void TestEquality()
	{
		Scope s1;
		s1["transform"] = glm::vec4(1);
		s1["rotation"] = glm::mat4(2);
		s1["intensity"] = 1.5f;
		s1["name"] = "light1";
		s1["range"] = 100;

		//compare with different size scope
		Scope s2;
		s2["transform"] = glm::vec4(1);
		s2["rotation"] = glm::mat4(2);
		s2["intensity"] = 1.5f;
		s2["name"] = "light1";
		TS_ASSERT(s2 != s1);

		//compare with scope with different datums
		Scope s3;
		s3["rotation"] = glm::mat4(2);
		s3["intensity"] = 1.5f;
		s3["name"] = "light1";
		s3["range"] = 100;
		s3["scale"] = glm::vec4(1);
		TS_ASSERT(s3 != s1);

		//compare with scope with different order of same datums
		Scope s4;
		s4["name"] = "light1";
		s4["transform"] = glm::vec4(1);
		s4["rotation"] = glm::mat4(2);
		s4["intensity"] = 1.5f;
		s4["range"] = 100;
		TS_ASSERT(s4 != s1);

		//compare with scope with same datums but different data
		Scope s5;
		s5["transform"] = glm::vec4(10);
		s5["rotation"] = glm::mat4(2);
		s5["intensity"] = 1.5f;
		s5["name"] = "light1";
		s5["range"] = 101;
		TS_ASSERT(s5 != s1);

		//compare with the same scope
		Scope s6;
		s6["transform"] = glm::vec4(1);
		s6["rotation"] = glm::mat4(2);
		s6["intensity"] = 1.5f;
		s6["name"] = "light1";
		s6["range"] = 100;
		TS_ASSERT(s6 == s1);

		//self equality
		TS_ASSERT(s1 == s1);
	}

	void TestFindName()
	{
		std::string name;
		Scope parent;
		Scope* child = parent.AppendScope("one");

		//find existing scope
		TS_ASSERT(parent.FindName(*child, name));
		TS_ASSERT_EQUALS(name, "one");

		//find non existing scope
		Scope* scope = new Scope();
		TS_ASSERT(parent.FindName(*scope, name) == false);
		TS_ASSERT_EQUALS(name, "");

		//find with null data
		//TS_ASSERT_THROWS(parent.FindName(nullptr, name), std::exception);

		delete scope;
	}

	void TestOrphan()
	{
		std::string name;
		Scope parent;

		//orphan internal scope
		Scope* child = parent.AppendScope("one");
		Datum& d = child->Append("id");
		d = 10;
		TS_ASSERT(parent.FindName(*child, name));
		TS_ASSERT_EQUALS(name, "one");

		parent.AppendScope("two");
		child->Orphan();
		parent.Adopt(*child, "two");
		TS_ASSERT(parent.FindName(*child, name));
		TS_ASSERT_EQUALS(name, "two");

		//orphan and adopt on external scope
		Scope* s1 = new Scope();
		Scope* s2 = new Scope();
		Scope* scopeArray[2] = { s1, s2 };
		Datum& d1 = parent.Append("ext");
		d1.SetStorage(scopeArray, 2);

		TS_ASSERT_THROWS_NOTHING(s1->Orphan());
		TS_ASSERT_THROWS(parent.Adopt(*s1, "ext", 1), std::exception);

		delete s1;
		delete s2;
	}

	void TestCompareStructure()
	{
		Scope s1;
		Datum& d1 = s1.Append("name");
		d1.Set("x", 0);
		d1.Set("y", 1);
		Datum& d2 = s1.Append("id");
		d2.Set(100, 0);
		d2.Set(101, 1);

		//compare with scope with different table size
		Scope s2;
		Datum& d3 = s2.Append("name");
		d3.Set("x", 0);
		d3.Set("y", 1);
		TS_ASSERT(s1.CompareStructure(s2) == false);

		//compare with scope with different datum structure
		Scope s3;
		Datum& d4 = s3.Append("id");
		d4.Set(100, 0);
		d4.Set(101, 1);
		Datum& d5 = s3.Append("id1");
		d5.Set("x", 0);
		d5.Set("y", 1);
		TS_ASSERT(s1.CompareStructure(s3) == false);

		//compare with scope with different datum type
		Scope s4;
		Datum& d6 = s4.Append("name");
		d6.Set(1.1f, 0);
		d6.Set(1.2f, 1);
		Datum& d7 = s4.Append("id");
		d7.Set(100, 0);
		d7.Set(101, 1);
		TS_ASSERT(s1.CompareStructure(s4) == false);

		//compare with scope with different datum size
		Scope s5;
		Datum& d8 = s5.Append("name");
		d8.Set("x", 0);
		Datum& d9 = s5.Append("id");
		d9.Set(100, 0);
		d9.Set(101, 1);
		TS_ASSERT(s1.CompareStructure(s5) == false);

		//compare with the same scope
		Scope s6;
		Datum& d10 = s6.Append("id");
		d10.Set(101, 0);
		d10.Set(102, 1);
		Datum& d11 = s6.Append("name");
		d11.Set("X", 0);
		d11.Set("z", 1);
		TS_ASSERT(s1.CompareStructure(s6));

		//self equality
		TS_ASSERT(s1.CompareStructure(s1));
	}
};