/**	@file Event.h
*	@brief Declaration of the templated Event class
*/

#pragma once
#include "EventPublisher.h"
#include "Slist.h"

namespace Library
{
	/**	@class Event
	*	@brief class that handles subscriber registrations and holds the event arguments
	*/
	template <typename EventType>
	class Event final : public EventPublisher
	{
		RTTI_DECLARATIONS(Event,EventPublisher)
	public:

		/**	@brief constructor to initialise the event
		*	@param the payload
		*	@param if the message should be automatically deleted after it is sent
		*/
		Event(const EventType& message, bool deleteAfterPublishing=true);

		/**	@brief Default destructor */
		virtual ~Event() = default;

		/**	@brief Add the subscriber to the list of subscribers
		*	@param the subscriber to add
		*/
		static void Subscribe(const EventSubscriber* subscriber);

		/**	@brief Remove the subscriber to from the list of subscribers
		*	@param the subscriber to remove
		*/
		static void UnSubscribe(const EventSubscriber* subscriber);

		/**	@brief Remove all subscribers for the event */
		static void UnSubscribeAll();

		/**	@brief Returns the number of subscribers for this event
		*	@param the subscriber count
		*/
		static std::uint32_t SubscriberCount();

		/**	@brief Return the payload of the event
		*	@param the event payload
		*/
		const EventType& Message() const;

	private:
		EventType mMessage; ///< payload
		static SList<EventSubscriber*> mSubscribers; ///< list of subscribers for the event
		static std::mutex mEventLock; ///< the mutex that locks the event
	};
}

#include "Event.inl"