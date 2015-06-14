/**	@file EventQueue.h
*	@brief Declaration of the event queue class
*/

#pragma once
#include "EventPublisher.h"
#include <chrono>
#include <mutex>

namespace Library
{
	/**	@class EventQueue
	*	@brief class that hold and delivers messages through publishers
	*/
	class EventQueue final
	{
	public:
		/**	@brief Default constructor */
		EventQueue() = default;

		/**	@brief Default destructor.
		*	If there are messages left in the queue when application exits, they are ignoredm since they are no longer relevant.
		*/
		~EventQueue();

		/**	@brief Add the message to the event queue. If there is no delay, it will be sent immediately without adding to the queue
		*	@param the current time in the world
		*	@param the delay for the message
		*/
		void Enqueue(EventPublisher* publisher, const std::chrono::high_resolution_clock::time_point& currentTime, 
			const std::chrono::milliseconds& delay = std::chrono::milliseconds(0)); //shared ptr ref

		/**	@brief Relay the message immediately without queueing it
		*	@param the event to relay
		*/
		void Send(const EventPublisher* publisher) const;

		/**	@brief Update the queue, relaying expired messages
		*	@param the game time in the world	
		*/
		void Update(const GameTime& gameTime);

		/**	@brief Empty the message queue, sending expired messages
		*	@param the current time in the world
		*/
		void Clear(const GameTime& currentTime);

		/**	@brief Returns if the queue contains events
		*	@return true if the queue has no events	in it
		*/
		bool IsEmpty() const;

		/**	@brief Returns the number of events in the queue
		*	@return the number of events queued
		*/
		std::uint32_t Count() const;

	private:
		mutable std::mutex mQueueMutex; ///< mutex that locks queue
		SList<EventPublisher*> mEvents; ///< list of events in the queue
	};
}
