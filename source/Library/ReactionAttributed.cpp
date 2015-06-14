#include "pch.h"
#include "ReactionAttributed.h"
#include <cstdint>

namespace Library
{
	RTTI_DEFINITIONS(ReactionAttributed)

	ReactionAttributed::ReactionAttributed(const std::string& name)
		:Reaction(name)
	{
		INTERNAL_ATTRIBUTE("Subtype", Datum::DatumType::String, nullptr, 0)

		Populate();

		mSubType = Find("Subtype"); //caching

		//subcribe to event
		Event<EventMessageAttributed>::Subscribe(this);
	}

	void ReactionAttributed::AddSubtype(const std::string& subtype)
	{
		mSubType->Set(subtype, UINT32_MAX); //add to the end of the array
	}

	const Datum* ReactionAttributed::SubTypes() const
	{
		return mSubType;
	}

	void ReactionAttributed::Notify(const EventPublisher& publisher)
	{
		Event<EventMessageAttributed>* eventMsg = publisher.As<Event<EventMessageAttributed>>();
		
		if (eventMsg == nullptr)
		{
			throw std::exception("Invalid event received");
		}
		
		EventMessageAttributed& payload = const_cast<EventMessageAttributed&>(eventMsg->Message());

		if (ContainsSubtype(payload.Subtype()))
		{
			//copy the arguments
			CopyAuxillaryAttributes(payload);

			//getting the world state from the world in the payload
			auto& worldState = payload.GetWorld()->GetWorldState();
			ActionList::Update(const_cast<WorldState&>(worldState));
		}
	}

	bool ReactionAttributed::ContainsSubtype(const std::string& subtype) const
	{
		for (std::uint32_t i = 0; i < mSubType->Size(); ++i)
		{
			std::string& type = mSubType->Get<std::string>(i);
			if (type == subtype)
			{
				return true;
			}
		}

		return false;
	}

	void ReactionAttributed::Update(WorldState& worldState)
	{
		//do nothing
	}

	ReactionAttributed::~ReactionAttributed()
	{
		//unregister from event
		Event<EventMessageAttributed>::UnSubscribe(this);
	}
}