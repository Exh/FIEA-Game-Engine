/**	@file UnsubscribeReaction.h
*	Declaration of the UnsubscribeReaction class
*/

#pragma once
#include "Reaction.h"

using namespace Library;

namespace Test
{
	/**	@class
	*	@brief
	*/
	class UnSubscribeReaction : public Reaction
	{
		RTTI_DECLARATIONS(UnSubscribeReaction, Reaction)
	public:

		/**	@brief Constructor to default name and subscribe to event attributed events */
		UnSubscribeReaction(const std::string& name = "");

		/**	@brief Constructor to default name and subscribe to event attributed events */
		virtual ~UnSubscribeReaction();

		/**	@brief Receives the message notification from the publisher
		*	@param the publisher of the event
		*/
		virtual void Notify(const EventPublisher& publisher) override;
		
		/**	@brief reaction update which does nothing, to suppress it from being treated as an action during world update
		*	@param the state of the world
		*/
		virtual void Update(WorldState& worldState) override;

		static int UnsubscribeCount; //count for testing
	};

	ACTION_FACTORY(UnSubscribeReaction)
}
