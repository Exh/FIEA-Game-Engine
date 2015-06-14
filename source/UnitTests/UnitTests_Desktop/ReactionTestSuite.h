#pragma once

#include <cxxtest/TestSuite.h>
#include "vld.h"

#include "pch.h"
#include "Shujinko.h"

using namespace Library;
using namespace Test;

class ReactionTestSuite : public CxxTest::TestSuite
{

public:
	void TestActionEventCreate()
	{
		//create action event without factory
		World world;
		Action* newAction = world.CreateAction("ActionEvent", "event");
		TS_ASSERT_EQUALS(newAction, nullptr);

		//with factory
		ActionEventFactory aeFactory;
		newAction = world.CreateAction("ActionEvent", "event");
		TS_ASSERT_DIFFERS(newAction, nullptr);
		TS_ASSERT(newAction->Is("ActionEvent"));
	}

	void TestReactionCreate()
	{
		//create reaction without factory
		World world;
		Action* newAction = world.CreateAction("ReactionAttributed", "rxn");
		TS_ASSERT_EQUALS(newAction, nullptr);

		//with factory
		ReactionAttributedFactory raFactory;
		newAction = world.CreateAction("ReactionAttributed", "rxn");
		TS_ASSERT_DIFFERS(newAction, nullptr);
		TS_ASSERT(newAction->Is("ReactionAttributed"));
		
		TS_ASSERT_EQUALS(Event<EventMessageAttributed>::SubscriberCount(), 1);
	}

	void TestReactionSubtypes()
	{
		ReactionAttributed rxn;
		TS_ASSERT_EQUALS(rxn.SubTypes()->Size(),0);

		//add subtypes
		rxn.AddSubtype("type1");
		rxn.AddSubtype("type2");
		rxn.AddSubtype("type3");
		rxn.AddSubtype("type4");
		TS_ASSERT_EQUALS(rxn.SubTypes()->Size(),4);
		
		//check if it has a present subtype
		TS_ASSERT(rxn.ContainsSubtype("type1"));

		//other subtypes
		TS_ASSERT(rxn.ContainsSubtype("something else")==false);
	}

	void TestCreateActionEventsFromXml()
	{
		ActionEventFactory aeFactory;

		XmlParseMaster master;
		World parsedWorld;

		TableSharedData sharedData(&parsedWorld);
		master.SetSharedData(&sharedData);

		XmlParseHelperTable helper;
		master.AddHelper(helper);
		XmlParseHelperAction actionHelper;
		master.AddHelper(actionHelper);

		const std::string& xmlString = "<world name=\"w\"><action name=\"axn\">"
			"<integer name=\"Delay\" value=\"1\" index=\"0\" />"
			"<string name=\"Subtype\" value=\"type\" index=\"0\"/>"
			"</action></world>";
		TS_ASSERT_THROWS_NOTHING(master.Parse(xmlString.c_str(), xmlString.length(), true, true));

		//setting time in the world
		auto& time = const_cast<GameTime&>(parsedWorld.GetGameTime());
		auto currentTime = std::chrono::high_resolution_clock::now();
		time.SetCurrentTime(currentTime);

		TS_ASSERT_EQUALS(parsedWorld.GetEventQueue().Count(), 0);

		//test that an event was queued
		parsedWorld.Update();
		TS_ASSERT_EQUALS(parsedWorld.GetEventQueue().Count(), 1);
	}

	void TestCreateReactionsFromXml()
	{
		ReactionAttributedFactory aeFactory;
		IncrementActionFactory incFactory;

		XmlParseMaster master;
		World parsedWorld;

		TableSharedData sharedData(&parsedWorld);
		master.SetSharedData(&sharedData);

		XmlParseHelperTable helper;
		master.AddHelper(helper);
		XmlParseHelperAction actionHelper;
		master.AddHelper(actionHelper);

		TS_ASSERT_EQUALS(Event<EventMessageAttributed>::SubscriberCount(), 0);

		const std::string& xmlString = "<world name=\"w\">"
			"<reaction name=\"rxn\">"
			"<string name=\"Subtype\" value=\"type\" index=\"0\"/>"
			"<increment name=\"add\" />"
			"</reaction></world>";
		TS_ASSERT_THROWS_NOTHING(master.Parse(xmlString.c_str(), xmlString.length(), true, true));

		//test that a subscriber was added
		TS_ASSERT_EQUALS(Event<EventMessageAttributed>::SubscriberCount(), 1); 
			
		auto& time = const_cast<GameTime&>(parsedWorld.GetGameTime());
		auto currentTime = std::chrono::high_resolution_clock::now();
		time.SetCurrentTime(currentTime);

		//updating reaction doesnt call update on actions inside it
		TS_ASSERT_EQUALS(IncrementAction::mUpdateCount, 0);
		parsedWorld.Update();
		TS_ASSERT_EQUALS(IncrementAction::mUpdateCount, 0);
	}
	
	void TestArgumentCopying()
	{
		ReactionAttributedFactory raFactory;
		ActionEventFactory aeFactory;

		XmlParseMaster master;
		World parsedWorld;

		TableSharedData sharedData(&parsedWorld);
		master.SetSharedData(&sharedData);

		XmlParseHelperTable helper;
		master.AddHelper(helper);
		XmlParseHelperAction actionHelper;
		master.AddHelper(actionHelper);

		const std::string& xmlString = "<world name=\"world\">"
			"<action name = \"Start\">"
			"<string name = \"Subtype\" index = \"0\" value =\"init\" />"
			"<integer name =\"a\" value =\"1\" />"
			"<string name =\"b\" value =\"temp\" />"
			"<float name =\"c\" value = \"10.0f\" />"
			"</action>"
			"<reaction name = \"StartReaction\">"
			"<string name = \"Subtype\" index = \"0\" value = \"init\" />"
			"</reaction>"
			"</world>";
		TS_ASSERT_THROWS_NOTHING(master.Parse(xmlString.c_str(), xmlString.length(), true, true));

		auto& time = const_cast<GameTime&>(parsedWorld.GetGameTime());
		auto currentTime = std::chrono::high_resolution_clock::now();
		time.SetCurrentTime(currentTime);
		
		//updating world to let the action event send an event to the reaction without delay
		parsedWorld.Update();

		//get the reaction
		auto rxn=parsedWorld.Actions()->Find("StartReaction")->GetTable();
		
		//find each of the 3 arguments and check if they are present and have the same value
		Datum* a = rxn->Find("a");
		TS_ASSERT_DIFFERS(a, nullptr);
		TS_ASSERT_EQUALS(*a, 1);
		
		Datum* b = rxn->Find("b");
		TS_ASSERT_DIFFERS(b, nullptr);
		TS_ASSERT_EQUALS(*b, "temp");

		Datum* c = rxn->Find("c");
		TS_ASSERT_DIFFERS(c, nullptr);
		TS_ASSERT_EQUALS(*c, 10.0f);
	}

	void TestSetOffCorrectReaction()
	{
		ReactionAttributedFactory raFactory;
		ActionEventFactory aeFactory;
		IncrementActionFactory incFactory;

		XmlParseMaster master;
		World parsedWorld;

		TableSharedData sharedData(&parsedWorld);
		master.SetSharedData(&sharedData);

		XmlParseHelperTable helper;
		master.AddHelper(helper);
		XmlParseHelperAction actionHelper;
		master.AddHelper(actionHelper);

		const std::string& xmlString = "<world name=\"world\">"
			"<action name=\"Start\">"
			"<string name=\"Subtype\" index=\"0\" value=\"init\" />"
			"</action>"
			"<reaction name=\"StartReaction\">"
			"<string name=\"Subtype\" index=\"0\" value=\"init\" />"
			"<increment name=\"add\" />"
			"</reaction>"
			"</world>";
		TS_ASSERT_THROWS_NOTHING(master.Parse(xmlString.c_str(), xmlString.length(), true, true));

		IncrementAction::mUpdateCount = 0;
		TS_ASSERT_EQUALS(IncrementAction::mUpdateCount, 0);

		auto& time = const_cast<GameTime&>(parsedWorld.GetGameTime());
		auto currentTime = std::chrono::high_resolution_clock::now();
		time.SetCurrentTime(currentTime);

		//send the event without delay
		parsedWorld.Update();

		//check if the event was received
		TS_ASSERT_EQUALS(IncrementAction::mUpdateCount, 1);
	}

	void TestDontSetOffIncorrectReaction()
	{
		ReactionAttributedFactory raFactory;
		ActionEventFactory aeFactory;
		IncrementActionFactory incFactory;

		XmlParseMaster master;
		World parsedWorld;

		TableSharedData sharedData(&parsedWorld);
		master.SetSharedData(&sharedData);

		XmlParseHelperTable helper;
		master.AddHelper(helper);
		XmlParseHelperAction actionHelper;
		master.AddHelper(actionHelper);

		const std::string& xmlString = "<world name=\"world\">"
				"<action name=\"EnemyKill\">"
				"<string name=\"Subtype\" index=\"0\" value=\"enemy die\" />"
				"</action>"
				"<reaction name=\"StartReaction\">"
				"<string name=\"Subtype\" index=\"0\" value=\"init\" />"
				"<increment name=\"add\" />"
				"</reaction>"
				"</world>";
		TS_ASSERT_THROWS_NOTHING(master.Parse(xmlString.c_str(), xmlString.length(), true, true));

		IncrementAction::mUpdateCount = 0;
		TS_ASSERT_EQUALS(IncrementAction::mUpdateCount, 0);

		auto& time = const_cast<GameTime&>(parsedWorld.GetGameTime());
		auto currentTime = std::chrono::high_resolution_clock::now();
		time.SetCurrentTime(currentTime);
		parsedWorld.Update();

		//test that the event was received because the reaction had a different sub type
		TS_ASSERT_EQUALS(IncrementAction::mUpdateCount, 0);
	}

	void TestActionToReactionXML()
	{
		SectorFactory sectorFactory;
		ShujinkoFactory shuFactory;
		ActionEventFactory aeFactory;
		ReactionAttributedFactory raFactory;
		IncrementActionFactory incFactory;
		DecrementActionFactory decFactory;

		XmlParseMaster master;
		World parsedWorld;

		TableSharedData sharedData(&parsedWorld);
		master.SetSharedData(&sharedData);

		XmlParseHelperTable helper;
		master.AddHelper(helper);
		XmlParseHelperAction actionHelper;
		master.AddHelper(actionHelper);

		TS_ASSERT_EQUALS(parsedWorld.GetEventQueue().Count(), 0);
		TS_ASSERT_EQUALS(Event<EventMessageAttributed>::SubscriberCount(), 0);

		TS_ASSERT_THROWS_NOTHING(master.ParseFromFile("Data/Reaction.xml"));

		TS_ASSERT_EQUALS(Event<EventMessageAttributed>::SubscriberCount(), 2);

		//resetting counters
		IncrementAction::mUpdateCount = 0;
		DecrementAction::mUpdateCount = 0;

		auto& time = const_cast<GameTime&>(parsedWorld.GetGameTime());
		auto currentTime = std::chrono::high_resolution_clock::now();
		time.SetCurrentTime(currentTime);
		
		//nothing is queued
		TS_ASSERT_EQUALS(parsedWorld.GetEventQueue().Count(), 0);

		parsedWorld.Update();

		//the event without the delay EnemyKill was fired and processed
		//the event with delay Start was queued
		TS_ASSERT_EQUALS(parsedWorld.GetEventQueue().Count(), 1); //new event queued
		TS_ASSERT_EQUALS(IncrementAction::mUpdateCount, 0); //event not yet fired
		TS_ASSERT_EQUALS(DecrementAction::mUpdateCount, -1); //delay-less event was proceesed

		//advance time
		time.SetCurrentTime(currentTime + std::chrono::milliseconds(2));

		//note: the events fire again
		parsedWorld.Update();

		//the event without delay was fired again
		//the event with delay expired was delivered
		//another event with delay was fired and queued
		TS_ASSERT_EQUALS(parsedWorld.GetEventQueue().Count(), 1); //the new event not the old one
		TS_ASSERT_EQUALS(IncrementAction::mUpdateCount, 1); //old event was processed
		TS_ASSERT_EQUALS(DecrementAction::mUpdateCount, -2); //delay-less event processed again
	}
};