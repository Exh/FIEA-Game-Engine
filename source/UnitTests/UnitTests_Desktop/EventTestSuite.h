#pragma once

#include <cxxtest/TestSuite.h>
#include "vld.h"

#include "pch.h"
#include "AutoSaveArgs.h"
#include "Foo.h"
#include "AutoSaveSubscriber.h"

using namespace Library;
using namespace Test;

class EventTestSuite : public CxxTest::TestSuite
{
public:
	void TestSubscription()
	{
		AutoSaveArgs saveArgs("location1");
		Event<AutoSaveArgs> autoSaveEvent(saveArgs);

		Foo foo;
		Event<Foo> fooEvent(foo);

		//test that subscribing to one event doesnt subscribe to all events
		TS_ASSERT_EQUALS(Event<AutoSaveArgs>::SubscriberCount(), 0);
		TS_ASSERT_EQUALS(Event<Foo>::SubscriberCount(), 0);
		
		AutoSaveSubscriber subscriber;
		Event<AutoSaveArgs>::Subscribe(&subscriber);

		TS_ASSERT_EQUALS(Event<AutoSaveArgs>::SubscriberCount(), 1);
		TS_ASSERT_EQUALS(Event<Foo>::SubscriberCount(), 0);

		//subscribing to the same event again -> leads to copies of the message as the subscriber is added again
		Event<AutoSaveArgs>::Subscribe(&subscriber);
		TS_ASSERT_EQUALS(Event<AutoSaveArgs>::SubscriberCount(), 2);

		//unsubscribe
		Event<AutoSaveArgs>::UnSubscribe(&subscriber);
		TS_ASSERT_EQUALS(Event<AutoSaveArgs>::SubscriberCount(), 1);

		//unsubscribe all
		Event<AutoSaveArgs>::UnSubscribeAll();
		TS_ASSERT_EQUALS(Event<AutoSaveArgs>::SubscriberCount(), 0);
	}

	void TestQueueing()
	{
		AutoSaveArgs saveArgs("hallway");
		Event<AutoSaveArgs> autoSaveEvent(saveArgs,false);

		AutoSaveSubscriber subscriber;
		Event<AutoSaveArgs>::Subscribe(&subscriber);
		TS_ASSERT_EQUALS(subscriber.mMessageReceivedCount, 0);

		GameTime gameTime;
		auto timePoint = std::chrono::high_resolution_clock::now();
		gameTime.SetCurrentTime(timePoint);

		EventQueue queue;
		TS_ASSERT_EQUALS(queue.Count(), 0);
		TS_ASSERT(queue.IsEmpty());

		//queue event without delay and test receipt -> event not deleted
		queue.Enqueue(&autoSaveEvent, gameTime.CurrentTime());
		TS_ASSERT_EQUALS(queue.Count(),0);
		TS_ASSERT(queue.IsEmpty());
		TS_ASSERT_EQUALS(subscriber.mMessageReceivedCount, 1);

		//queue event without delay and test receipt -> event deleted
		Event<AutoSaveArgs>* event1 = new Event<AutoSaveArgs>(saveArgs);
		queue.Enqueue(event1, gameTime.CurrentTime());
		TS_ASSERT_EQUALS(queue.Count(), 0);
		TS_ASSERT(queue.IsEmpty());
		TS_ASSERT_EQUALS(subscriber.mMessageReceivedCount, 2);

		//queue with delay -> event to delete and event to not delete
		Event<AutoSaveArgs>* event2 = new Event<AutoSaveArgs>(saveArgs);
		queue.Enqueue(event2, gameTime.CurrentTime(),std::chrono::milliseconds(2));
		queue.Enqueue(&autoSaveEvent, gameTime.CurrentTime(), std::chrono::milliseconds(2));

		//event not sent before expiry
		queue.Update(gameTime);
		TS_ASSERT_EQUALS(subscriber.mMessageReceivedCount, 2);
		TS_ASSERT_EQUALS(queue.Count(), 2);

		//events sent after expiry, both removed from queue and delete only if requested
		gameTime.SetCurrentTime(gameTime.CurrentTime() + std::chrono::milliseconds(3));
		queue.Update(gameTime);
		TS_ASSERT_EQUALS(subscriber.mMessageReceivedCount, 4);
		TS_ASSERT_EQUALS(queue.Count(), 0);

		//send
		Event<AutoSaveArgs>* event3 = new Event<AutoSaveArgs>(saveArgs);
		queue.Send(event3);
		TS_ASSERT_EQUALS(queue.Count(), 0);
		TS_ASSERT(queue.IsEmpty());
		TS_ASSERT_EQUALS(subscriber.mMessageReceivedCount, 5);

		//clear the queue
		queue.Enqueue(&autoSaveEvent, gameTime.CurrentTime(), std::chrono::milliseconds(2));
		queue.Enqueue(&autoSaveEvent, gameTime.CurrentTime(), std::chrono::milliseconds(2));
		TS_ASSERT_EQUALS(queue.Count(), 2);

		queue.Clear(gameTime);
		TS_ASSERT_EQUALS(queue.Count(), 0);
		TS_ASSERT(queue.IsEmpty());
		TS_ASSERT_EQUALS(subscriber.mMessageReceivedCount, 5);
		
	}

	void TestEventProperties()
	{
		AutoSaveArgs saveArgs("hallway");
		Event<AutoSaveArgs> autoSaveEvent(saveArgs, false);

		GameTime gameTime;
		auto timePoint = std::chrono::high_resolution_clock::now();
		gameTime.SetCurrentTime(timePoint);

		EventQueue queue;

		queue.Enqueue(&autoSaveEvent, gameTime.CurrentTime(), std::chrono::milliseconds(5));

		TS_ASSERT_EQUALS(autoSaveEvent.Message().mSaveLocation, saveArgs.mSaveLocation);

		TS_ASSERT_EQUALS(autoSaveEvent.IsExpired(gameTime.CurrentTime()), false);
		TS_ASSERT_EQUALS(autoSaveEvent.Delay(), std::chrono::milliseconds(5));
		TS_ASSERT_EQUALS(autoSaveEvent.TimeEnqueued(), gameTime.CurrentTime());

		//check if expiry is calculated correctly
		autoSaveEvent.SetTime(gameTime.CurrentTime() + std::chrono::milliseconds(6));

		TS_ASSERT(autoSaveEvent.IsExpired(gameTime.CurrentTime()+std::chrono::milliseconds(10)));

	}
};