/**	@file EnqueueReaction.cpp
*	Definitions of the EnqueueReaction class
*/

#include "EnqueueReaction.h"
#include "pch.h"

namespace Test
{
	RTTI_DEFINITIONS(EnqueueReaction)

	int EnqueueReaction::EnqueueCount = 0;

	EnqueueReaction::EnqueueReaction(const std::string& name)
		:Reaction(name)
	{
		Event<EventMessageAttributed>::Subscribe(this);
	}

	void EnqueueReaction::Notify(const EventPublisher& publisher)
	{
		Event<EventMessageAttributed>* eventMsg = publisher.As<Event<EventMessageAttributed>>();

		if (eventMsg == nullptr)
		{
			throw std::exception("Invalid event received");
		}

		EventMessageAttributed& payload = const_cast<EventMessageAttributed&>(eventMsg->Message());

		if (payload.Subtype()=="enemy die")
		{
			//copy the arguments
			CopyAuxillaryAttributes(payload);

			//getting the world state from the world in the payload
			auto& worldState = payload.GetWorld()->GetWorldState();
			ActionList::Update(const_cast<WorldState&>(worldState));

			//create a new event and enqueue it here
			EventMessageAttributed payload;
			payload.SetSubtype("act");
			payload.SetWorld(worldState.mWorld);

			//copy the auxillary attributes from this into the payload
			payload.CopyAuxillaryAttributes(*this);

			//create the event with the payload
			Event<EventMessageAttributed>* newEvent = new Event<EventMessageAttributed>(payload);

			//get the queue and enqueue the event
			EventQueue& queue = const_cast<EventQueue&>(worldState.mWorld->GetEventQueue());
			queue.Enqueue(newEvent, worldState.mGameTime->CurrentTime(), std::chrono::milliseconds(1));

			//update the count for testing
			EnqueueCount++;
		}
	}

	void EnqueueReaction::Update(WorldState& worldState)
	{
		//do nothing
	}

	EnqueueReaction::~EnqueueReaction()
	{
		Event<EventMessageAttributed>::UnSubscribe(this);
	}
}