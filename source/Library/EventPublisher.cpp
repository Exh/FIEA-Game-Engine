/**	@file EventPublisher.cpp
*	@brief Definition of the EventPublisher class
*/

#include "pch.h"

using namespace std;

namespace Library
{
	RTTI_DEFINITIONS(EventPublisher)

	SList<EventSubscriber*>* EventPublisher::mSubscribers = nullptr;

	EventPublisher::EventPublisher(const SList<EventSubscriber*>& subscribers,const std::mutex& mutex, bool deleteAfterPublishing) //
		: mDeleteAfterPublishing(deleteAfterPublishing), mDelay(), mEnqueuedTime()
	{
		mSubscribers = const_cast<SList<EventSubscriber*>*>(&subscribers);
		mMutexPtr = const_cast<std::mutex*>(&mutex);
	}

	void EventPublisher::SetTime(const std::chrono::high_resolution_clock::time_point& currentTime, const std::chrono::milliseconds& delay)
	{
		lock_guard<mutex> lock(*mMutexPtr);
		mEnqueuedTime = currentTime;
		mDelay = delay;
	}
	
	const std::chrono::high_resolution_clock::time_point& EventPublisher::TimeEnqueued() const
	{
		lock_guard<mutex> lock(*mMutexPtr);
		return mEnqueuedTime;
	}

	const std::chrono::milliseconds& EventPublisher::Delay() const
	{
		lock_guard<mutex> lock(*mMutexPtr);
		return mDelay;
	}

	bool EventPublisher::IsExpired(const std::chrono::high_resolution_clock::time_point& currentTime) const
	{
		lock_guard<mutex> lock(*mMutexPtr);
		return (currentTime > (mEnqueuedTime + mDelay));
	}

	void EventPublisher::Deliver() const
	{
		std::vector<future<void>> futures;

		{
			lock_guard<mutex> lock(*mMutexPtr);
			for (auto& it : *mSubscribers)
			{
				futures.emplace_back(async(launch::async, &EventSubscriber::Notify, it, std::ref(*this)));
			}
		}

		//wait for futures
		for (auto& f : futures)
		{
			f.get();
		}
	}

	bool EventPublisher::DeleteAfterPublishing() const
	{
		lock_guard<mutex> lock(*mMutexPtr);
		return mDeleteAfterPublishing;
	}
}