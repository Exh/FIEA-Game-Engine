#include "pch.h"
#include "ActionEvent.h"

namespace Library
{
	RTTI_DEFINITIONS(ActionEvent)

	ActionEvent::ActionEvent(const std::string& name, const std::string& subtype, std::uint32_t delay)
		: Action(name)
	{
		INTERNAL_ATTRIBUTE("Subtype", Datum::DatumType::String, nullptr, 1)
		INTERNAL_ATTRIBUTE("Delay", Datum::DatumType::Integer, &delay, 1)

		Populate();
		
		mSubtypeDatum = Find("Subtype"); //caching
		mSubtypeDatum->Set(subtype); //same as setting default from signature

		mDelayDatum = Find("Delay");
	}

	void ActionEvent::Update(WorldState& worldState)
	{
		//create the payload
		EventMessageAttributed payload;
		payload.SetSubtype(mSubtypeDatum->Get<std::string>());
		payload.SetWorld(worldState.mWorld);
		
		//copy the auxillary attributes from this into the payload
		payload.CopyAuxillaryAttributes(*this);

		//create the event with the payload
		Event<EventMessageAttributed>* newEvent = new Event<EventMessageAttributed>(payload);

		//get the queue and enqueue the event
		EventQueue& queue = const_cast<EventQueue&>(worldState.mWorld->GetEventQueue());
		queue.Enqueue(newEvent, worldState.mGameTime->CurrentTime(), std::chrono::milliseconds(mDelayDatum->Get<std::int32_t>()));
	}

	const std::string& ActionEvent::SubType() const
	{
		return mSubtypeDatum->Get<std::string>();
	}

	std::uint32_t ActionEvent::Delay() const
	{
		return mDelayDatum->Get<std::uint32_t>();
	}

	void ActionEvent::SetSubType(const std::string& subtype)
	{
		mSubtypeDatum->Set(subtype);
	}

	void ActionEvent::SetDelay(std::uint32_t delay)
	{
		mDelayDatum->Set(std::int32_t(delay));
	}
}