/**	@file EnqueueActionEvent.h
*	Declaration of the EnqueueActionEvent class
*/

#include "EnqueueActionEvent.h"
#include "pch.h"

namespace Test
{
	RTTI_DEFINITIONS(EnqueueActionEvent)

		int EnqueueActionEvent::UpdateCount = 0;

	EnqueueActionEvent::EnqueueActionEvent(const std::string& name)
		:Action(name)
	{
	}

	void EnqueueActionEvent::Update(WorldState& worldState)
	{
		//create and enqueue a new event
		//create the payload
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
		UpdateCount++;
	}
}
