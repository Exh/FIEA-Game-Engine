/**	@file EventQueue.cpp
*	@brief Definitions of the EventQueue class
*/

#include "pch.h"

using namespace std;

namespace Library
{
	EventQueue::~EventQueue()
	{
		Vector<EventPublisher*> toDelete;
		
		{
			lock_guard<mutex> queueLock(mQueueMutex);
			for (EventPublisher* it : mEvents)
			{
				if (it->DeleteAfterPublishing())
				{
					toDelete.PushBack(it);
				}
			}
		}
		
		for (std::uint32_t i = 0; i < toDelete.Size(); i++)
		{
			delete toDelete[i];
		}

	}

	void EventQueue::Enqueue(EventPublisher* publisher, const std::chrono::high_resolution_clock::time_point& currentTime,
		const std::chrono::milliseconds& delay)
	{
		//no delay, send it immediately
		if (delay == std::chrono::milliseconds(0))
		{
			Send(publisher);
		}
		//else add it to the queue
		else
		{
			//locking inside the publisher
			publisher->SetTime(currentTime, delay);

			lock_guard<mutex> queueLock(mQueueMutex);
			mEvents.PushBack(publisher);
		}
	}

	void EventQueue::Send(const EventPublisher* publisher) const
	{
		//locking inside the publisher
		publisher->Deliver();

		if (publisher->DeleteAfterPublishing())
		{
			delete publisher;
		}
	}

	void EventQueue::Update(const GameTime& gameTime)
	{
		std::vector<EventPublisher*> toDelete; //list of events to delete

		vector<future<void>> futures;

		{
			lock_guard<mutex> queueLock(mQueueMutex);

			for (EventPublisher* it : mEvents)
			{
				if (it->IsExpired(gameTime.CurrentTime()))
				{
					futures.emplace_back(async(launch::async, &EventPublisher::Deliver, it));

					toDelete.emplace_back(it); //note the event as something to delete
					//not deleting here so the queue iterators wont be invalidated during traversal through the queue
				}
			}
		}

		//wait for futures
		for (auto& f : futures)
		{
			f.get();
		}

		//remove the sent events and delete those events marked for delete
		{
			lock_guard<mutex> queueLock(mQueueMutex);
			for (std::uint32_t i = 0; i < toDelete.size(); i++)
			{
				mEvents.Remove(toDelete[i]);

				if (toDelete[i]->DeleteAfterPublishing())
				{
					delete toDelete[i];
				}
			}
		}

		//std::partition to separate expired vs nonexpired
		//std::foreach to deliver
		//std::erase
	}

	void EventQueue::Clear(const GameTime& gameTime)
	{
		//try to deliver expired events before clearing the queue
		Update(gameTime);

		lock_guard<mutex> queueLock(mQueueMutex);
		mEvents.Clear();
	}

	bool EventQueue::IsEmpty() const
	{
		lock_guard<mutex> queueLock(mQueueMutex);
		return mEvents.IsEmpty();
	}

	std::uint32_t EventQueue::Count() const
	{
		lock_guard<mutex> queueLock(mQueueMutex);
		return mEvents.Size();
	}
}