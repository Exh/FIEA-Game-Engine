/**	@file SubscribeReaction.cpp
*	Definitions of the SubscribeReaction class
*/

#include "SubscribeReaction.h"
#include "pch.h"
#include "AutoSaveArgs.h"

namespace Test
{
	RTTI_DEFINITIONS(SubscribeReaction)

	SubscribeReaction::SubscribeReaction(const std::string& name)
		:Reaction(name)
	{
		Event<EventMessageAttributed>::Subscribe(this);
	}

	void SubscribeReaction::Notify(const EventPublisher& publisher)
	{
		//same as reaction attributed
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

			//Subscribe to another event
			Event<AutoSaveArgs>::Subscribe(this);
		}
	}

	void SubscribeReaction::Update(WorldState& worldState)
	{
		//do nothing
	}

	SubscribeReaction::~SubscribeReaction()
	{
		Event<EventMessageAttributed>::UnSubscribe(this);
	}
}