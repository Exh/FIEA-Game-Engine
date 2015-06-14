/**	@file UnsubscribeReaction.cpp
*	definitions of the UnsubscribeReaction class
*/

#include "UnSubscribeReaction.h"
#include "pch.h"

namespace Test
{
	RTTI_DEFINITIONS(UnSubscribeReaction)

		UnSubscribeReaction::UnSubscribeReaction(const std::string& name)
		:Reaction(name)
	{
		Event<EventMessageAttributed>::Subscribe(this);
	}

	void UnSubscribeReaction::Notify(const EventPublisher& publisher)
	{
		Event<EventMessageAttributed>* eventMsg = publisher.As<Event<EventMessageAttributed>>();

		if (eventMsg == nullptr)
		{
			throw std::exception("Invalid event received");
		}

		EventMessageAttributed& payload = const_cast<EventMessageAttributed&>(eventMsg->Message());

		if (payload.Subtype() == "init")
		{
			//copy the arguments
			CopyAuxillaryAttributes(payload);

			//getting the world state from the world in the payload
			auto& worldState = payload.GetWorld()->GetWorldState();
			ActionList::Update(const_cast<WorldState&>(worldState));

			//UnSubscribe from the current event
			Event<EventMessageAttributed>::UnSubscribe(this);
		}
	}

	void UnSubscribeReaction::Update(WorldState& worldState)
	{
		//do nothing
	}

	UnSubscribeReaction::~UnSubscribeReaction()
	{
		Event<EventMessageAttributed>::UnSubscribe(this);
	}
}