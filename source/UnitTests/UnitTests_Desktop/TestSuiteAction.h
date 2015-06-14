#pragma once

#include <cxxtest/TestSuite.h>
#include "vld.h"

#include "pch.h"
#include "IncrementAction.h"
#include "DecrementAction.h"
#include "Kaijuu.h"

using namespace Library;
using namespace Test;

class TestSuiteAction : public CxxTest::TestSuite
{
public:
	void TestConstruction()
	{		
		//action
		IncrementAction inc("inc");
		TS_ASSERT_EQUALS(inc.Size(), 3); //Contains this, name, subactions
		TS_ASSERT_EQUALS(inc.Name(), "inc");
		TS_ASSERT_EQUALS(inc.SubActions()->Size(), 0);

		//action list
		ActionList list("list");
		TS_ASSERT_EQUALS(list.Size(), 3); //Contains this, name, subactions
		TS_ASSERT_EQUALS(list.Name(), "list");
		TS_ASSERT_EQUALS(list.SubActions()->Size(), 0);
	}

	void TestMoveAction()
	{
		IncrementAction* inc = new IncrementAction("inc");
		TS_ASSERT_EQUALS(inc->GetWorld(), nullptr);
		TS_ASSERT_EQUALS(inc->GetSector(), nullptr);
		TS_ASSERT_EQUALS(inc->GetEntity(), nullptr);
		TS_ASSERT_EQUALS(inc->GetAction(), nullptr);

		//move into world
		World w("w");
		inc->SetWorld(w);
		TS_ASSERT_EQUALS(w.Actions()->Size(), 1);
		TS_ASSERT_EQUALS(inc->GetWorld(), &w);
		TS_ASSERT_EQUALS(inc->GetSector(), nullptr);
		TS_ASSERT_EQUALS(inc->GetEntity(), nullptr);
		TS_ASSERT_EQUALS(inc->GetAction(), nullptr);

		//move into sector
		Sector s("s");
		inc->SetSector(s);
		TS_ASSERT_EQUALS(s.Actions()->Size(), 1);
		TS_ASSERT_EQUALS(inc->GetWorld(), nullptr);
		TS_ASSERT_EQUALS(inc->GetSector(), &s);
		TS_ASSERT_EQUALS(inc->GetEntity(), nullptr);
		TS_ASSERT_EQUALS(inc->GetAction(), nullptr);

		//move into entity
		Entity e("e");
		inc->SetEntity(e);
		TS_ASSERT_EQUALS(e.Actions()->Size(), 1);
		TS_ASSERT_EQUALS(inc->GetWorld(), nullptr);
		TS_ASSERT_EQUALS(inc->GetSector(), nullptr);
		TS_ASSERT_EQUALS(inc->GetEntity(), &e);
		TS_ASSERT_EQUALS(inc->GetAction(), nullptr);

		//move into another action
		ActionIf a("a");
		inc->SetAction(a);
		TS_ASSERT_EQUALS(a.SubActions()->Size(), 1);
		TS_ASSERT_EQUALS(inc->GetWorld(), nullptr);
		TS_ASSERT_EQUALS(inc->GetSector(), nullptr);
		TS_ASSERT_EQUALS(inc->GetEntity(), nullptr);
		TS_ASSERT_EQUALS(inc->GetAction(), &a);

		//move into action list
		ActionList l("l");
		inc->SetAction(l);
		TS_ASSERT_EQUALS(l.SubActions()->Size(), 1);
		TS_ASSERT_EQUALS(inc->GetWorld(), nullptr);
		TS_ASSERT_EQUALS(inc->GetSector(), nullptr);
		TS_ASSERT_EQUALS(inc->GetEntity(), nullptr);
		TS_ASSERT_EQUALS(inc->GetAction(), &l);
	}

	void TestCreateAction()
	{
		TS_ASSERT(Factory<Action>::ContainsFactory("IncrementAction") == false);

		IncrementActionFactory incFactory;

		TS_ASSERT(Factory<Action>::ContainsFactory("IncrementAction"));

		//create in world
		World world("w");
		TS_ASSERT_EQUALS(world.Actions()->Size(), 0);
		Action* a1= world.CreateAction("IncrementAction", "inc");
		TS_ASSERT_EQUALS(world.Actions()->Size(), 1);

		//create in sector
		Sector sector("s");
		TS_ASSERT_EQUALS(sector.Actions()->Size(), 0);
		Action* a2 = sector.CreateAction("IncrementAction", "inc");
		TS_ASSERT_EQUALS(sector.Actions()->Size(), 1);

		//create in entity
		Entity entity("e");
		TS_ASSERT_EQUALS(entity.Actions()->Size(), 0);
		Action* a3 = entity.CreateAction("IncrementAction", "inc");
		TS_ASSERT_EQUALS(entity.Actions()->Size(), 1);

		//in another action
		IncrementAction action("a");
		TS_ASSERT_EQUALS(action.SubActions()->Size(), 0);
		Action* a4 = action.CreateSubAction("IncrementAction", "inc");
		TS_ASSERT_EQUALS(action.SubActions()->Size(), 1);

		//in actionlist
		ActionList list("l");
		TS_ASSERT_EQUALS(list.SubActions()->Size(), 0);
		Action* a5 = list.CreateSubAction("IncrementAction", "inc");
		TS_ASSERT_EQUALS(list.SubActions()->Size(), 1);

		delete a1;
		delete a2;
		delete a3;
		delete a4;
		delete a5;
	}

	void TestUpdate()
	{
		WorldState temp;
		IncrementActionFactory incFactory;

		//action
		IncrementAction inc("inc");
		TS_ASSERT_EQUALS(inc.mUpdateCount, 0);
		inc.Update(temp);
		TS_ASSERT_EQUALS(inc.mUpdateCount, 1);

		//action list
		ActionList list("list");
		Action* a1 = list.CreateSubAction("IncrementAction", "inc1");
		Action* a2 = list.CreateSubAction("IncrementAction", "inc2");
		list.Update(temp);
		TS_ASSERT_EQUALS(IncrementAction::mUpdateCount, 3);

		delete a1;
		delete a2;
	}

	void TestCreateWithoutFactory()
	{
		//confirm factories arent present
		TS_ASSERT(Factory<Action>::ContainsFactory("ActionList") == false);
		TS_ASSERT(Factory<Action>::ContainsFactory("ActionIf") == false);
		TS_ASSERT(Factory<Action>::ContainsFactory("IncrementAction") == false);

		//creating from xml
		XmlParseMaster master;
		World parsedWorld;

		TableSharedData sharedData(&parsedWorld);
		master.SetSharedData(&sharedData);

		XmlParseHelperTable helper;
		master.AddHelper(helper);
		XmlParseHelperAction actionHelper;
		master.AddHelper(actionHelper);

		const std::string& xmlString1 = "<world name=\"w\"><if name=\"if\"></if></world>";
		TS_ASSERT_THROWS(master.Parse(xmlString1.c_str(), xmlString1.length(), true, true), std::exception);

		//creating by calling create action method
		Sector sector("s");
		Action* action = sector.CreateAction("actions", "list");
		TS_ASSERT_EQUALS(action, nullptr); 
	}

	void TestCreateActionIfFromXml()
	{
		ActionIfFactory ifFactory;
		SectorFactory sFactory;
		KaijuuFactory kFactory;
		ActionListFactory alFactory;

		XmlParseMaster master;
		World parsedWorld;

		TableSharedData sharedData(&parsedWorld);
		master.SetSharedData(&sharedData);

		XmlParseHelperTable helper;
		master.AddHelper(helper);
		XmlParseHelperAction actionHelper;
		master.AddHelper(actionHelper);

		//in world
		const std::string& xmlString = "<world name=\"w\"><if name=\"if\"></if></world>";
		TS_ASSERT_THROWS_NOTHING(master.Parse(xmlString.c_str(), xmlString.length(), true, true));
		TS_ASSERT_EQUALS(parsedWorld.Name(), "w");
		TS_ASSERT_EQUALS(parsedWorld.Actions()->Size(), 1);
		TS_ASSERT(parsedWorld.Actions()->Find("if") != nullptr);

		//trying to create under invalid element
		const std::string& xmlString1 = "<world name=\"w\"><integer name=\"int\"><if name=\"if\"></if></integer></world>";
		TS_ASSERT_THROWS(master.Parse(xmlString1.c_str(), xmlString1.length(), true, true),std::exception);

		//then and else cant be under anything but if
		const std::string& xmlString2 = "<world name=\"w\"><integer name=\"int\"><then name=\"then\"></then></integer></world>";
		TS_ASSERT_THROWS(master.Parse(xmlString2.c_str(), xmlString2.length(), true, true), std::exception);

		const std::string& xmlString3 = "<world name=\"w\"><integer name=\"int\"><else name=\"else\"></else></integer></world>";
		TS_ASSERT_THROWS(master.Parse(xmlString3.c_str(), xmlString3.length(), true, true), std::exception);

		//in sector
		const std::string& xmlString4 = "<world name=\"w\"><sector name=\"s\"><if name=\"if1\" /></sector></world>";
		TS_ASSERT_THROWS_NOTHING(master.Parse(xmlString4.c_str(), xmlString4.length(), true, true));

		Sector* sector = parsedWorld.Sectors()->Find("s")->GetTable(UINT32_MAX)->As<Sector>();
		TS_ASSERT_EQUALS(sector->Actions()->Size(), 1);
		TS_ASSERT(sector->Actions()->Find("if1") != nullptr);

		//in entity
		const std::string& xmlString5 = "<world name=\"w\"><sector name=\"s\"><entity name=\"e\" class=\"Kaijuu\"><if name=\"if2\" /></entity></sector></world>";
		TS_ASSERT_THROWS_NOTHING(master.Parse(xmlString5.c_str(), xmlString5.length(), true, true));
		
		sector = parsedWorld.Sectors()->Find("s")->GetTable(UINT32_MAX)->As<Sector>();
		Entity* kai = sector->Entities()->Find("e")->GetTable(UINT32_MAX)->As<Kaijuu>();
		TS_ASSERT_EQUALS(kai->Actions()->Size(), 1);
		TS_ASSERT(kai->Actions()->Find("if2") != nullptr);

		//in action
		const std::string& xmlString6 = "<world name = \"w\"><sector name=\"s\"><entity name=\"e\" class=\"Kaijuu\"><if name=\"if3\"><if name=\"nest\"></if></if></entity></sector></world>";
		TS_ASSERT_THROWS_NOTHING(master.Parse(xmlString6.c_str(), xmlString6.length(), true, true));

		sector = parsedWorld.Sectors()->Find("s")->GetTable(UINT32_MAX)->As<Sector>();
		kai = sector->Entities()->Find("e")->GetTable(UINT32_MAX)->As<Kaijuu>();
		Action* if1 = kai->Actions()->Find("if3")->GetTable(UINT32_MAX)->As<Action>();
		TS_ASSERT_EQUALS(if1->SubActions()->Size(), 1);
		TS_ASSERT(if1->SubActions()->Find("nest") != nullptr);

		//in actionlist
		const std::string& xmlString7 = "<world name = \"w\"><sector name=\"s\"><entity name=\"e\" class=\"Kaijuu\"><actions name=\"acts\"><if name=\"nest\"></if></actions></entity></sector></world>";
		TS_ASSERT_THROWS_NOTHING(master.Parse(xmlString7.c_str(), xmlString7.length(), true, true));

		sector = parsedWorld.Sectors()->Find("s")->GetTable(UINT32_MAX)->As<Sector>();
		kai = sector->Entities()->Find("e")->GetTable(UINT32_MAX)->As<Kaijuu>();
		if1 = kai->Actions()->Find("acts")->GetTable(UINT32_MAX)->As<Action>();
		TS_ASSERT_EQUALS(if1->SubActions()->Size(), 1);
		TS_ASSERT(if1->SubActions()->Find("nest") != nullptr);

		//create without no name
		const std::string& xmlString8 = "<world name=\"world\"><if /></world>";
		TS_ASSERT_THROWS(master.Parse(xmlString8.c_str(), xmlString8.length(), true, true),std::exception);
	}

	void TestIf()
	{
		ActionIfFactory ifFactory;
		IncrementActionFactory incFactory;
		DecrementActionFactory decFactory;
		ActionListFactory actionsFactory;

		XmlParseMaster master;
		World parsedWorld;

		TableSharedData sharedData(&parsedWorld);
		master.SetSharedData(&sharedData);

		XmlParseHelperTable helper;
		master.AddHelper(helper);
		XmlParseHelperAction actionHelper;
		master.AddHelper(actionHelper);

		IncrementAction::mUpdateCount = 0;
		TS_ASSERT_EQUALS(IncrementAction::mUpdateCount, 0);
		TS_ASSERT_EQUALS(DecrementAction::mUpdateCount, 0);

		//normal -> condition = 1 -> if executes -> increment counter 
		const std::string& xmlString1 = "<world name=\"world\">"
			"<if name=\"if1\"><integer name=\"condition\">1</integer>"
			"<then name=\"then1\"><actions name=\"do\"><increment name=\"add\" /></actions></then>"
			"<else name=\"else1\"><decrement name=\"sub\" /></else></if></world>";

		TS_ASSERT_THROWS_NOTHING(master.Parse(xmlString1.c_str(), xmlString1.length(), true, true));

		parsedWorld.Update();

		TS_ASSERT_EQUALS(IncrementAction::mUpdateCount, 1);
		TS_ASSERT_EQUALS(DecrementAction::mUpdateCount, 0);

		//if without condition -> condition = 1
		World world;
		sharedData.SetCurrentScope(&world);

		const std::string& xmlString2 = "<world name=\"world\">"
			"<if name=\"if1\">"
			"<then name=\"then1\"><actions name=\"do\"><increment name=\"add\" /></actions></then>"
			"<else name=\"else1\"><decrement name=\"sub\" /></else></if></world>";

		TS_ASSERT_THROWS_NOTHING(master.Parse(xmlString2.c_str(), xmlString2.length(), true, true));
		world.Update();
		TS_ASSERT_EQUALS(IncrementAction::mUpdateCount, 2);
		TS_ASSERT_EQUALS(DecrementAction::mUpdateCount, 0);

		//if without then -> condition = 1 -> nothing happens
		World world1;
		sharedData.SetCurrentScope(&world1);

		const std::string& xmlString3 = "<world name=\"world\">"
			"<if name=\"if1\">"
			"<else name=\"else1\"><decrement name=\"sub\" /></else></if></world>";

		TS_ASSERT_THROWS_NOTHING(master.Parse(xmlString3.c_str(), xmlString3.length(), true, true));
		world1.Update();
		TS_ASSERT_EQUALS(IncrementAction::mUpdateCount, 2);
		TS_ASSERT_EQUALS(DecrementAction::mUpdateCount, 0);

		//else -> condition = 0 -> decrement counter
		World world2;
		sharedData.SetCurrentScope(&world2);

		const std::string& xmlString4 = "<world name=\"world\">"
			"<if name=\"if1\"><integer name=\"condition\" index=\"0\">0</integer>"
			"<else name=\"else1\"><decrement name=\"sub\" /></else></if></world>";

		TS_ASSERT_THROWS_NOTHING(master.Parse(xmlString4.c_str(), xmlString4.length(), true, true));
		world2.Update();
		TS_ASSERT_EQUALS(IncrementAction::mUpdateCount, 2);
		TS_ASSERT_EQUALS(DecrementAction::mUpdateCount, -1);

		//nested if -> condition = 0 in both -> decrement counter
		World world3;
		sharedData.SetCurrentScope(&world3);

		const std::string& xmlString5 = "<world name=\"w\"><if name=\"if1\">"
			"<integer name=\"condition\" index=\"0\" value=\"0\" />"
			"<else name=\"e\"><if name=\"if2\"><integer name=\"condition\" index=\"0\" value=\"0\" />"
			"<else name=\"e\"><decrement name=\"sub\" /></else></if></else></if></world>";

		TS_ASSERT_THROWS_NOTHING(master.Parse(xmlString5.c_str(), xmlString5.length(), true, true));
		world3.Update();
		TS_ASSERT_EQUALS(IncrementAction::mUpdateCount, 2);
		TS_ASSERT_EQUALS(DecrementAction::mUpdateCount, -2);

		//test when then or else has no action -> nothing happens
		World world4;
		sharedData.SetCurrentScope(&world4);

		const std::string& xmlString6 = "<world name=\"w\"><if name=\"if1\">"
			"<integer name=\"condition\" index=\"0\" value=\"0\" />"
			"<else name=\"e\"></else></if></world>";

		TS_ASSERT_THROWS_NOTHING(master.Parse(xmlString6.c_str(), xmlString6.length(), true, true));
		world4.Update();
		TS_ASSERT_EQUALS(IncrementAction::mUpdateCount, 2);
		TS_ASSERT_EQUALS(DecrementAction::mUpdateCount, -2);
	}

};