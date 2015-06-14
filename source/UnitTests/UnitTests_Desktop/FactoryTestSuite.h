#pragma once

#include <cxxtest/TestSuite.h>
#include "vld.h"

#include "pch.h"
#include "Kaijuu.h"
#include "Shujinko.h"

using namespace Library;
using namespace Test;

class FactoryTestSuite : public CxxTest::TestSuite
{
public:
	CONCRETE_FACTORY(Shujinko, Library::RTTI)
	CONCRETE_FACTORY(Kaijuu,Library::RTTI)

	void TestFactoryRegister()
	{
		TS_ASSERT(Factory<RTTI>::ContainsFactory("Shujinko") == false);
		TS_ASSERT(Factory<RTTI>::ContainsFactory("Kaijuu") == false);

		{
			//test if the factories are added properly
			ShujinkoFactory shuFactory;
			KaijuuFactory kaiFactory;

			TS_ASSERT(Factory<RTTI>::ContainsFactory("Shujinko"));
			TS_ASSERT(Factory<RTTI>::ContainsFactory("Kaijuu"));
			TS_ASSERT_EQUALS(Factory<RTTI>::FactoryCount(), 2);
		}

		TS_ASSERT(Factory<RTTI>::ContainsFactory("Shujinko") == false);
		TS_ASSERT(Factory<RTTI>::ContainsFactory("Kaijuu") == false);
	}

	void TestFind()
	{
		//test if the added factories can be found
		ShujinkoFactory shuFactory;
		KaijuuFactory kaiFactory;

		TS_ASSERT_EQUALS(Factory<RTTI>::Find("Shujinko"), &shuFactory);
		TS_ASSERT_EQUALS(Factory<RTTI>::Find("Kaijuu"), &kaiFactory);
		TS_ASSERT_EQUALS(Factory<RTTI>::Find("Something else"), nullptr);
	}

	void TestCreate()
	{
		//test creation of product from factories
		ShujinkoFactory shuFactory;
		KaijuuFactory kaiFactory;

		auto* shujinko1 = Factory<RTTI>::Create("Shujinko");
		TS_ASSERT(shujinko1->Is("Shujinko"));

		auto* kaijuu1 = Factory<RTTI>::Create("Kaijuu");
		auto* kaijuu2 = Factory<RTTI>::Create("Kaijuu");
		TS_ASSERT(kaijuu1->Is("Kaijuu"));
		TS_ASSERT(kaijuu2->Is("Kaijuu"));
		TS_ASSERT(kaijuu1 != kaijuu2);

		delete shujinko1;
		delete kaijuu1;
		delete kaijuu2;
	}

	void TestIteration()
	{
		//test walking through the hashmap
		ShujinkoFactory shuFactory;
		KaijuuFactory kaiFactory;

		int count = 0;

		for (auto it = Factory<RTTI>::begin(); it != Factory<RTTI>::end(); ++it)
		{
			count++;
		}

		TS_ASSERT_EQUALS(Factory<RTTI>::FactoryCount(), count);
	}

	void TestClassName()
	{
		ShujinkoFactory shuFactory;
		KaijuuFactory kaiFactory;

		TS_ASSERT_EQUALS(shuFactory.ClassName(), "Shujinko");
		TS_ASSERT_EQUALS(kaiFactory.ClassName(), "Kaijuu");
	}

	void TestAdd()
	{
		ShujinkoFactory shuFactory;
		KaijuuFactory kaiFactory;

		TS_ASSERT_EQUALS(Factory<RTTI>::FactoryCount(), 2);

		Factory<RTTI>::Add(shuFactory);
		TS_ASSERT_EQUALS(Factory<RTTI>::FactoryCount(), 2);

		//Factory<RTTI>::Add(nullptr);
		//TS_ASSERT_EQUALS(Factory<RTTI>::FactoryCount(), 2);
	}

	void TestRemove()
	{
		ShujinkoFactory shuFactory;
		KaijuuFactory kaiFactory;

		Factory<RTTI>::Remove(shuFactory);
		TS_ASSERT_EQUALS(Factory<RTTI>::FactoryCount(), 1);

		TS_ASSERT(!Factory<RTTI>::ContainsFactory("Shujinko"));
	}
};