/**	@file Event.inl
*	@brief Definition of the Event class
*/

#include "Event.h"
#include <mutex>

namespace Library
{
	template <typename EventType>
	RTTI_DEFINITIONS(Event<EventType>)

	template <typename EventType>
	SList<EventSubscriber*> Event<EventType>::mSubscribers = SList<EventSubscriber*>();

	template <typename EventType>
	std::mutex Event<EventType>::mEventLock = std::mutex();

	template <typename EventType>
	Event<EventType>::Event(const EventType& message, bool deleteAfterPublishing) //passing in the static variables to the base class
		:EventPublisher(mSubscribers, mEventLock, deleteAfterPublishing), mMessage(message)
	{
	}

	template <typename EventType>
	std::uint32_t Event<EventType>::SubscriberCount()
	{
		std::lock_guard<std::mutex> lock(mEventLock);
		return mSubscribers.Size();
	}

	template <typename EventType>
	void Event<EventType>::Subscribe(const EventSubscriber* subscriber)
	{
		std::lock_guard<std::mutex> lock(mEventLock);
		//check present and then add
		mSubscribers.PushBack(const_cast<EventSubscriber*>(subscriber));
	}

	template <typename EventType>
	void Event<EventType>::UnSubscribe(const EventSubscriber* subscriber)
	{
		std::lock_guard<std::mutex> lock(mEventLock);
		mSubscribers.Remove(const_cast<EventSubscriber*>(subscriber));
	}
	
	template <typename EventType>
	void Event<EventType>::UnSubscribeAll()
	{
		std::lock_guard<std::mutex> lock(mEventLock);
		mSubscribers.Clear();
	}

	template <typename EventType>
	const EventType& Event<EventType>::Message() const
	{
		std::lock_guard<std::mutex> lock(mEventLock);
		return mMessage;
	}
}