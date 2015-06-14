/**	@file EventSubscriber.h
*	@brief Declaration of the Subscriber class
*/

#pragma once

namespace Library
{
	class EventPublisher;

	/**	@class EventSubscriber
	*	@brief the class that subscribes to the publisher's events
	*/
	class EventSubscriber
	{
	public:
		/**	@brief Default constructor */
		EventSubscriber() = default;

		/**	@brief Default destructor */
		virtual ~EventSubscriber() = default;

		/**	@brief Pure virtual method that concrete subscriber need to implement to decide how to handle the message */
		virtual void Notify(const EventPublisher& publisher) = 0;
	};
}