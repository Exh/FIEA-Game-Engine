/**	@file EnqueueReaction.h
*	Declaration of the EnqueueReaction class
*/

#pragma once
#include "Reaction.h"

using namespace Library;

namespace Test 
{
	/**	@class
	*	@brief
	*/
	class EnqueueReaction : public Reaction
	{
		RTTI_DECLARATIONS(EnqueueReaction, Reaction)

	public:

		/**	@brief Constructor to default name and subscribe to event attributed events */
		EnqueueReaction(const std::string& name="");

		/**	@brief Constructor to default name and subscribe to event attributed events */
		virtual ~EnqueueReaction();

		/**	@brief Receives the message notification from the publisher
		*	@param the publisher of the event
		*/
		virtual void Notify(const EventPublisher& publisher) override;

		/**	@brief reaction update which does nothing, to suppress it from being treated as an action during world update
		*	@param the state of the world
		*/
		virtual void Update(WorldState& worldState) override;

		static int EnqueueCount; //count for testing
	};

	ACTION_FACTORY(EnqueueReaction)
}
