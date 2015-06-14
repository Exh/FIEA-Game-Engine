#pragma once

#include <cxxtest/TestSuite.h>
#include "vld.h"

#include "pch.h"
#include "AutoSaveArgs.h"
#include "Foo.h"
#include "AutoSaveSubscriber.h"
#include "Shujinko.h"
#include "EnqueueActionEvent.h"
#include "EnqueueReaction.h"
#include "UnSubscribeReaction.h"
#include "SubscribeReaction.h"

using namespace Library;
using namespace Test;

class AsyncEventTestSuite : public CxxTest::TestSuite
{
public:
	void TestStress()
	{
		//just run the existing test with several threads
		const int threadCount = 1000;

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

		TS_ASSERT_THROWS_NOTHING(master.ParseFromFile("Data/Reaction.xml"));

		auto& time = const_cast<GameTime&>(parsedWorld.GetGameTime());
		auto currentTime = std::chrono::high_resolution_clock::now();		
		time.SetCurrentTime(currentTime);
		
		for (int i = 0; i < threadCount; i++)
		{
			parsedWorld.Update();
			time.SetCurrentTime(currentTime + std::chrono::milliseconds(1));
		}
	}

	void TestSubscribe()
	{
		//test when reactions subscribe inside notify
		const int threadCount = 1000;

		SectorFactory sectorFactory;
		ShujinkoFactory shuFactory;
		ActionEventFactory aeFactory;
		ReactionAttributedFactory raFactory;
		IncrementActionFactory incFactory;
		DecrementActionFactory decFactory;
		SubscribeReactionFactory qFactory;

		XmlParseMaster master;
		World parsedWorld;

		TableSharedData sharedData(&parsedWorld);
		master.SetSharedData(&sharedData);

		XmlParseHelperTable helper;
		master.AddHelper(helper);
		XmlParseHelperAction actionHelper;
		master.AddHelper(actionHelper);

		TS_ASSERT_THROWS_NOTHING(master.ParseFromFile("Data/Reaction.xml"));

		Action* action = parsedWorld.CreateAction("SubscribeReaction", "enq");

		auto& time = const_cast<GameTime&>(parsedWorld.GetGameTime());
		auto currentTime = std::chrono::high_resolution_clock::now();
		time.SetCurrentTime(currentTime);

		for (int i = 0; i < threadCount; i++)
		{
			parsedWorld.Update();
			time.SetCurrentTime(currentTime + std::chrono::milliseconds(1));
		}

		delete action;
	}

	void TestUnsubscribe()
	{
		//test when reactions unsubscribe inside notify
		const int threadCount = 1000;

		SectorFactory sectorFactory;
		ShujinkoFactory shuFactory;
		ActionEventFactory aeFactory;
		ReactionAttributedFactory raFactory;
		IncrementActionFactory incFactory;
		DecrementActionFactory decFactory;
		UnSubscribeReactionFactory qFactory;

		XmlParseMaster master;
		World parsedWorld;

		TableSharedData sharedData(&parsedWorld);
		master.SetSharedData(&sharedData);

		XmlParseHelperTable helper;
		master.AddHelper(helper);
		XmlParseHelperAction actionHelper;
		master.AddHelper(actionHelper);

		TS_ASSERT_THROWS_NOTHING(master.ParseFromFile("Data/Reaction.xml"));

		Action* action = parsedWorld.CreateAction("UnSubscribeReaction", "enq");

		auto& time = const_cast<GameTime&>(parsedWorld.GetGameTime());
		auto currentTime = std::chrono::high_resolution_clock::now();
		time.SetCurrentTime(currentTime);

		for (int i = 0; i < threadCount; i++)
		{
			parsedWorld.Update();
			time.SetCurrentTime(currentTime + std::chrono::milliseconds(1));
		}

		delete action;
	}

	void TestEnqueueMore_Action()
	{
		//test when actions queue events on update
		const int threadCount = 1000;

		SectorFactory sectorFactory;
		ShujinkoFactory shuFactory;
		ActionEventFactory aeFactory;
		ReactionAttributedFactory raFactory;
		IncrementActionFactory incFactory;
		DecrementActionFactory decFactory;
		EnqueueActionEventFactory qFactory;

		XmlParseMaster master;
		World parsedWorld;

		TableSharedData sharedData(&parsedWorld);
		master.SetSharedData(&sharedData);

		XmlParseHelperTable helper;
		master.AddHelper(helper);
		XmlParseHelperAction actionHelper;
		master.AddHelper(actionHelper);

		TS_ASSERT_THROWS_NOTHING(master.ParseFromFile("Data/Reaction.xml"));

		Action* action = parsedWorld.CreateAction("EnqueueActionEvent", "enq");

		auto& time = const_cast<GameTime&>(parsedWorld.GetGameTime());
		auto currentTime = std::chrono::high_resolution_clock::now();
		time.SetCurrentTime(currentTime);

		for (int i = 0; i < threadCount; i++)
		{
			parsedWorld.Update();
			time.SetCurrentTime(currentTime + std::chrono::milliseconds(1));
		}

		TS_ASSERT_EQUALS(EnqueueActionEvent::UpdateCount, threadCount);
		delete action;
	}

	void TestEnqueueMore_Reaction()
	{
		//test when reactions queue events on notify
		const int threadCount = 1000;

		SectorFactory sectorFactory;
		ShujinkoFactory shuFactory;
		ActionEventFactory aeFactory;
		ReactionAttributedFactory raFactory;
		IncrementActionFactory incFactory;
		DecrementActionFactory decFactory;
		EnqueueReactionFactory qFactory;

		XmlParseMaster master;
		World parsedWorld;

		TableSharedData sharedData(&parsedWorld);
		master.SetSharedData(&sharedData);

		XmlParseHelperTable helper;
		master.AddHelper(helper);
		XmlParseHelperAction actionHelper;
		master.AddHelper(actionHelper);

		TS_ASSERT_THROWS_NOTHING(master.ParseFromFile("Data/Reaction.xml"));

		Action* action = parsedWorld.CreateAction("EnqueueReaction", "enq");

		auto& time = const_cast<GameTime&>(parsedWorld.GetGameTime());
		auto currentTime = std::chrono::high_resolution_clock::now();
		time.SetCurrentTime(currentTime);

		for (int i = 0; i < threadCount; i++)
		{
			parsedWorld.Update();
			time.SetCurrentTime(currentTime + std::chrono::milliseconds(1));
		}

		TS_ASSERT_EQUALS(EnqueueReaction::EnqueueCount, threadCount);
		delete action;
	}
};
