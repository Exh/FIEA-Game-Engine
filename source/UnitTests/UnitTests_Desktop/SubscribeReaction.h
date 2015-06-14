/**	@file SubscribeReaction.h
*	Declaration of the SubscribeReaction class
*/

#pragma once
#include "Reaction.h"

using namespace Library;

namespace Test
{
	/**	@class
	*	@brief
	*/
	class SubscribeReaction : public Reaction
	{
		RTTI_DECLARATIONS(SubscribeReaction, Reaction)

	public:
		/**	@brief Constructor to default name and subscribe to event attributed events */
		SubscribeReaction(const std::string& name = "");

		/**	@brief Constructor to default name and subscribe to event attributed events */
		virtual ~SubscribeReaction();

		/**	@brief Receives the message notification from the publisher
		*	@param the publisher of the event
		*/
		virtual void Notify(const EventPublisher& publisher) override;
		
		/**	@brief reaction update which does nothing, to suppress it from being treated as an action during world update
		*	@param the state of the world
		*/
		virtual void Update(WorldState& worldState) override;

		static int SubscribeCount; //count for testing
	};

	ACTION_FACTORY(SubscribeReaction)
}
