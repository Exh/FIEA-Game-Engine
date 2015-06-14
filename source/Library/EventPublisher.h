/**	@file EventPublisher.h
*	@brief Declaration of the Publisher class
*/

#pragma once
#include "EventSubscriber.h"
#include "RTTI.h"
#include "Slist.h"
#include <chrono>
#include <mutex>

namespace Library
{
	/**	@class EventPublisher
	*	@brief class that sends out event notifications to subscribers
	*/
	class EventPublisher : public RTTI
	{
		RTTI_DECLARATIONS(EventPublisher,RTTI)

	public:
		/**	@brief Constructor that initialises the publisher
		*	@param address of the list of subscribers for the publisher
		*	@param true, if the event must be deleted after sending. If set to false, user is responsible for deleting created events
		*/
		EventPublisher(const SList<EventSubscriber*>& subscribers, const std::mutex& mutex, bool deleteAfterPublishing=true); 

		/**	@brief Default destructor */
		virtual ~EventPublisher()=default;

		/**	@brief Set the time of enqueue and delay for the event 
		*	@param time enqueued
		*	@param delay after which to deliver this event
		*/
		void SetTime(const std::chrono::high_resolution_clock::time_point& currentTime, 
			const std::chrono::milliseconds& delay = std::chrono::milliseconds(0));

		/**	@brief Return the time the event was queued
		*	@return enqueue time for the event
		*/
		const std::chrono::high_resolution_clock::time_point& TimeEnqueued() const;

		/**	@brief Delay after which to deliver the message
		*	@return delay for the event
		*/
		const std::chrono::milliseconds& Delay() const;

		/**	@brief returns if the event has expired based on the current time
		*	@param the current time in the world
		*	@return true if it has expired, false otherwise
		*/
		bool IsExpired(const std::chrono::high_resolution_clock::time_point& currentTime) const;

		/**	@brief Send the event to the subscribers */
		virtual void Deliver() const;

		/**	@brief flag to decide if the event should be deleted after it is sent.
		*	@return true, if the system deletes the event, false if the user is responsible for the event's delete
		*/
		bool DeleteAfterPublishing() const;

		//std::mutex& EventMutex() const;

	protected:
		static SList<EventSubscriber*>* mSubscribers; ///< address of the list of subscriber for each event type

		std::chrono::high_resolution_clock::time_point mEnqueuedTime;
		std::chrono::milliseconds mDelay;
		bool mDeleteAfterPublishing;

		std::mutex* mMutexPtr; ///< pointer to the mutex of the derived class
	};
}
