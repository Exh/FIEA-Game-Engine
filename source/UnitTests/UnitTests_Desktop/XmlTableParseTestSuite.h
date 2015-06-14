#pragma once

#include <cxxtest/TestSuite.h>
#include "vld.h"

#include "pch.h"

using namespace Library;

class XmlTableParserTestSuite : public CxxTest::TestSuite
{
public:
	void TestNestedScopes()
	{
		XmlParseMaster master;
		Scope parsedScope;

		TableSharedData sharedData(&parsedScope);
		master.SetSharedData(&sharedData);

		XmlParseHelperTable helper;
		master.AddHelper(helper);

		std::string xmlString = "<table name=\"current\"><table name=\"child\"><table name=\"grandchild\"></table><table name=\"grandchild1\"></table></table></table>";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);

		TS_ASSERT(parsedScope.Find("current") == nullptr);

		auto child = parsedScope.Find("child");
		TS_ASSERT(child!= nullptr);
		TS_ASSERT_EQUALS(child->GetType(), Datum::DatumType::Table);
		TS_ASSERT_EQUALS(child->Size(), 1); //size of the datum
		TS_ASSERT_EQUALS(child->GetTable()->Size(), 2);

		auto grandchild = child->GetTable()->Find("grandchild");
		TS_ASSERT(grandchild != nullptr);
		TS_ASSERT_EQUALS(grandchild->GetType(), Datum::DatumType::Table);
		TS_ASSERT_EQUALS(grandchild->Size(), 1);
		TS_ASSERT_EQUALS(grandchild->GetTable()->Size(), 0);
	}

	void TestNestedOthers()
	{
		//nesting in non table tags
		XmlParseMaster master;
		Scope parsedScope;

		TableSharedData sharedData(&parsedScope);
		master.SetSharedData(&sharedData);

		XmlParseHelperTable helper;
		master.AddHelper(helper);

		std::string xmlString = "<integer name=\"i1\"><float name=\"x\"/></integer>";
		TS_ASSERT_THROWS(master.Parse(xmlString.c_str(), xmlString.length(), true, true),std::exception);

		xmlString = "<float name=\"f1\"><float name=\"x\"/></float>";
		TS_ASSERT_THROWS(master.Parse(xmlString.c_str(), xmlString.length(), true, true), std::exception);

		xmlString = "<string name=\"s1\"><float name=\"x\"/></string>";
		TS_ASSERT_THROWS(master.Parse(xmlString.c_str(), xmlString.length(), true, true), std::exception);

		xmlString = "<vector name=\"v1\"><float name=\"x\"/></vector>";
		TS_ASSERT_THROWS(master.Parse(xmlString.c_str(), xmlString.length(), true, true), std::exception);

		xmlString = "<matrix name=\"m1\"><float name=\"x\"/></matrix>";
		TS_ASSERT_THROWS(master.Parse(xmlString.c_str(), xmlString.length(), true, true), std::exception);
	}

	void TestNameAndValueAttributes()
	{
		XmlParseMaster master;
		Scope parsedScope;

		TableSharedData sharedData(&parsedScope);
		master.SetSharedData(&sharedData);

		XmlParseHelperTable helper;
		master.AddHelper(helper);

		//no name attribute - name is required
		std::string xmlString = "<integer value=\"10\"></integer>";
		TS_ASSERT_THROWS(master.Parse(xmlString.c_str(), xmlString.length(), true, true), std::exception);

		//no value attribute - default the value
		xmlString = "<integer name=\"i2\"></integer>";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);
		TS_ASSERT_EQUALS(parsedScope.Size(), 1);
		TS_ASSERT_EQUALS(*(parsedScope.Find("i2")), 0);

		xmlString = "<float name=\"f2\"></float>";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);
		TS_ASSERT_EQUALS(parsedScope.Size(), 2);
		TS_ASSERT_EQUALS(*(parsedScope.Find("f2")), 0.0f);

		xmlString = "<string name=\"s2\"></string>";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);
		TS_ASSERT_EQUALS(parsedScope.Size(), 3);
		TS_ASSERT_EQUALS(*(parsedScope.Find("s2")), "");

		xmlString = "<vector name=\"v2\"></vector>";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);
		TS_ASSERT_EQUALS(parsedScope.Size(), 4);
		TS_ASSERT_EQUALS(*(parsedScope.Find("v2")), glm::vec4(0.0f));

		xmlString = "<matrix name=\"m2\"></matrix>";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);
		TS_ASSERT_EQUALS(parsedScope.Size(), 5);
		TS_ASSERT_EQUALS(*(parsedScope.Find("m2")), glm::mat4(0.0f));

		//having either value or inner text is the same
		xmlString = "<integer name=\"i_1\">15</integer>";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);

		xmlString = "<integer name=\"i_2\" value=\"15\" />";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);
		TS_ASSERT_EQUALS(*(parsedScope.Find("i_1")), *(parsedScope.Find("i_2")));

		//having both value and inner text -> prefernce over value attribute
		xmlString = "<integer name=\"i_3\" value=\"15\">25</integer>";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);
		TS_ASSERT_EQUALS(*(parsedScope.Find("i_3")), 15);

		//inner text in several lines
		std::string array[6] = { "<integer name=\"split\">", "1", "2", "3", "4", "</integer>" };
		master.Parse(array[0].c_str(), array[0].length(), true, false);
		master.Parse(array[1].c_str(), array[1].length(), false, false);
		master.Parse(array[2].c_str(), array[2].length(), false, false);
		master.Parse(array[3].c_str(), array[3].length(), false, false);
		master.Parse(array[4].c_str(), array[4].length(), false, false);
		master.Parse(array[5].c_str(), array[5].length(), false, true);
		TS_ASSERT_EQUALS(*(parsedScope.Find("split")), 1234);
	}

	void TestSizeAndIndexAttributes()
	{
		XmlParseMaster master;
		Scope parsedScope;

		TableSharedData sharedData(&parsedScope);
		master.SetSharedData(&sharedData);

		XmlParseHelperTable helper;
		master.AddHelper(helper);

		//has both and index -> set size to max of 2, parse one value and set at index
		//size > index
		std::string xmlString = "<integer name=\"gt_size\" size=\"5\" index=\"1\">1;2;3;4;5</integer>";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);
		auto& datum = *(parsedScope.Find("gt_size"));
		TS_ASSERT_EQUALS(datum.Size(), 5);
		TS_ASSERT_EQUALS(datum.Get<std::int32_t>(1), 1);

		//index > size
		xmlString = "<integer name=\"gt_index\" size=\"2\" index=\"5\">1;2;3;4;5</integer>";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);
		auto& datum1 = *(parsedScope.Find("gt_index"));
		TS_ASSERT_EQUALS(datum1.Size(), 6);
		TS_ASSERT_EQUALS(datum1.Get<std::int32_t>(5), 1);

		//has just size -> parse size number of data, default rest
		//too much data
		xmlString = "<integer name=\"too_much\" size=\"2\">1;2;3;4;5</integer>";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);
		auto& datum2 = *(parsedScope.Find("too_much"));
		TS_ASSERT_EQUALS(datum2.Size(), 2);
		TS_ASSERT_EQUALS(datum2.Get<std::int32_t>(0), 1);
		TS_ASSERT_EQUALS(datum2.Get<std::int32_t>(1), 2);

		//too little data
		xmlString = "<integer name=\"too_little\" size=\"3\">-11;</integer>";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);
		auto& datum3 = *(parsedScope.Find("too_little"));
		TS_ASSERT_EQUALS(datum3.Size(), 3);
		TS_ASSERT_EQUALS(datum3.Get<std::int32_t>(0), -11);
		TS_ASSERT_EQUALS(datum3.Get<std::int32_t>(1), 0);
		TS_ASSERT_EQUALS(datum3.Get<std::int32_t>(2), 0);

		//no data
		xmlString = "<integer name=\"all_alone\" size=\"3\" />";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);
		auto& datum4 = *(parsedScope.Find("all_alone"));
		TS_ASSERT_EQUALS(datum4.Size(), 3);
		TS_ASSERT_EQUALS(datum4.Get<std::int32_t>(0), 0);
		TS_ASSERT_EQUALS(datum4.Get<std::int32_t>(1), 0);
		TS_ASSERT_EQUALS(datum4.Get<std::int32_t>(2), 0);

		//has just index -> just parse one value and set at that index
		//no data
		xmlString = "<integer name=\"no_one\" index=\"2\"></integer>";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);
		auto& datum5 = *(parsedScope.Find("no_one"));
		TS_ASSERT_EQUALS(datum5.Size(), 3);
		TS_ASSERT_EQUALS(datum5.Get<std::int32_t>(2), 0);

		//extra data
		xmlString = "<integer name=\"not_alone\" index=\"1\">1;2;3;4;5;</integer>";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);
		auto& datum6 = *(parsedScope.Find("not_alone"));
		TS_ASSERT_EQUALS(datum6.Size(), 2);
		TS_ASSERT_EQUALS(datum6.Get<std::int32_t>(1), 1);

		//has neither size nor index -> parse all the data
		xmlString = "<integer name=\"evens\">0;2;4;6;8;10</integer>";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);
		
		auto& datum7 = *(parsedScope.Find("evens"));
		for (int i = 0; i < 6; i++)
		{
			TS_ASSERT_EQUALS(datum7.Get<std::int32_t>(i), i * 2);
		}
	}

	void TestAddingToSameName()
	{
		XmlParseMaster master;
		Scope parsedScope;

		TableSharedData sharedData(&parsedScope);
		master.SetSharedData(&sharedData);

		XmlParseHelperTable helper;
		master.AddHelper(helper);

		std::string xmlString = "<integer name=\"i\" value=\"10\" />";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);
		TS_ASSERT_EQUALS(*(parsedScope.Find("i")), 10);
		TS_ASSERT_EQUALS(parsedScope.Size(), 1);

		//appending to same type data to existing name
		xmlString = "<integer name=\"i\" value=\"20\" />";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);
		auto& datum = *(parsedScope.Find("i"));

		TS_ASSERT_EQUALS(datum.Get<std::int32_t>(0), 10);
		TS_ASSERT_EQUALS(datum.Get<std::int32_t>(1), 20);
		TS_ASSERT_EQUALS(parsedScope.Size(), 1);

		//adding different type data to existing name
		xmlString = "<string name=\"i\" value=\"apple\" />";
		TS_ASSERT_THROWS(master.Parse(xmlString.c_str(), xmlString.length(), true, true),std::exception);
	}

	void TestValidScalars()
	{
		XmlParseMaster master;
		Scope parsedScope;

		TableSharedData sharedData(&parsedScope);
		master.SetSharedData(&sharedData);

		XmlParseHelperTable helper;
		master.AddHelper(helper);

		//normal scalar int
		std::string xmlString = "<integer name=\"int1\" value=\"10\"/>";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);
		TS_ASSERT_EQUALS(parsedScope.Size(), 1);
		TS_ASSERT_EQUALS(*(parsedScope.Find("int1")), 10);

		//normal scalar float
		xmlString = "<float name=\"float1\" value=\"1.1\" />";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);
		TS_ASSERT_EQUALS(parsedScope.Size(), 2);
		TS_ASSERT_EQUALS(*(parsedScope.Find("float1")), 1.1f);

		//normal scalar string
		xmlString = "<string name=\"string1\" value=\"apple\" />";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);
		TS_ASSERT_EQUALS(parsedScope.Size(), 3);
		TS_ASSERT_EQUALS(*(parsedScope.Find("string1")), "apple");

		//normal scalar matrix
		xmlString = "<matrix name=\"mat1\" value=\"5\" />";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);
		TS_ASSERT_EQUALS(parsedScope.Size(), 4);
		TS_ASSERT_EQUALS(*(parsedScope.Find("mat1")), glm::mat4(5));

		//normal scalar vector
		xmlString = "<vector name=\"vec1\" value=\"12\" />";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);
		TS_ASSERT_EQUALS(parsedScope.Size(), 5);
		TS_ASSERT_EQUALS(*(parsedScope.Find("vec1")), glm::vec4(12));
	}

	void TestValidVectors()
	{ 
		XmlParseMaster master;
		Scope parsedScope;

		TableSharedData sharedData(&parsedScope);
		master.SetSharedData(&sharedData);

		XmlParseHelperTable helper;
		master.AddHelper(helper);

		//normal array of ints
		std::string xmlString = "<integer name=\"i\">1;2;3;4</integer>";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);

		auto datum = parsedScope.Find("i");
		TS_ASSERT_EQUALS(datum->GetType(), Datum::DatumType::Integer);
		for (std::uint32_t i = 0; i < datum->Size(); i++)
		{
			TS_ASSERT_EQUALS(datum->Get<std::int32_t>(i), i+1);
		}

		//normal array of floats
		xmlString = "<float name=\"f\">1;2;3;4</float>";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);

		datum = parsedScope.Find("f");
		TS_ASSERT_EQUALS(datum->GetType(), Datum::DatumType::Float);
		for (std::uint32_t i = 0; i < datum->Size(); i++)
		{
			TS_ASSERT_EQUALS(datum->Get<float>(i), (float)i+1);
		}

		//normal array of vectors
		xmlString = "<vector name=\"v\">1;2;3;4</vector>";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);

		datum = parsedScope.Find("v");
		TS_ASSERT_EQUALS(datum->GetType(), Datum::DatumType::Vector);
		for (std::uint32_t i = 0; i < datum->Size(); i++)
		{
			TS_ASSERT_EQUALS(datum->Get<glm::vec4>(i), glm::vec4(i+1));
		}

		//normal array of matrices
		xmlString = "<matrix name=\"m\">1;2;3;4</matrix>";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);

		datum = parsedScope.Find("m");
		TS_ASSERT_EQUALS(datum->GetType(), Datum::DatumType::Matrix);
		for (std::uint32_t i = 0; i < datum->Size(); i++)
		{
			TS_ASSERT_EQUALS(datum->Get<glm::mat4>(i), glm::mat4(i + 1));
		}

		//normal array of strings
		xmlString = "<string name=\"s\">1;2;3;4</string>";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);

		datum = parsedScope.Find("s");
		TS_ASSERT_EQUALS(datum->GetType(), Datum::DatumType::String);
		TS_ASSERT_EQUALS(datum->Get<std::string>(0), "1");
		TS_ASSERT_EQUALS(datum->Get<std::string>(1), "2");
		TS_ASSERT_EQUALS(datum->Get<std::string>(2), "3");
		TS_ASSERT_EQUALS(datum->Get<std::string>(3), "4");
	}

	void TestFromFile()
	{
		XmlParseMaster master;
		Scope parsedScope;

		TableSharedData sharedData(&parsedScope);
		master.SetSharedData(&sharedData);

		XmlParseHelperTable helper;
		master.AddHelper(helper);

		TS_ASSERT_THROWS_NOTHING(master.ParseFromFile("Data/TableDef.xml"));

		TS_ASSERT_EQUALS(parsedScope.Size(), 3);

		auto scope1 = parsedScope.Find("internalScalar")->GetTable();
		TS_ASSERT_EQUALS(scope1->Size(), 5);

		auto scope2 = parsedScope.Find("internalVector")->GetTable();
		TS_ASSERT_EQUALS(scope2->Size(), 5);
	}

	void TestSharedDataClone()
	{
		XmlParseMaster master;
		Scope parsedScope;

		TableSharedData sharedData(&parsedScope);
		master.SetSharedData(&sharedData);

		XmlParseHelperTable helper;
		master.AddHelper(helper);

		std::string xmlString = "<integer name=\"i\" value=\"10\" />";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);

		TableSharedData* copy = reinterpret_cast<TableSharedData*>(sharedData.Clone());
		TS_ASSERT(copy->IsClone());
		TS_ASSERT_EQUALS(*(copy->GetParsedScope()), *(sharedData.GetParsedScope()));

		delete copy;
	}
};
