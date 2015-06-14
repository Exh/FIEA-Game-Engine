#include "pch.h"
#include "EventMessageAttributed.h"

namespace Library
{
	RTTI_DEFINITIONS(EventMessageAttributed)

	EventMessageAttributed::EventMessageAttributed(const std::string& subtype, World* world)
		:mSubtype(subtype), mWorld(world)
	{
		//take these out
	/*	EXTERNAL_ATTRIBUTE("Subtype",Datum::DatumType::String,&mSubtype,1)
		EXTERNAL_ATTRIBUTE("World",Datum::DatumType::Pointer,&mWorld,1)

		Populate();*/
	}

	const std::string& EventMessageAttributed::Subtype() const
	{
		return mSubtype;
	}

	void EventMessageAttributed::SetSubtype(const std::string& subtype)
	{
		mSubtype = subtype;
	}

	World* EventMessageAttributed::GetWorld() const
	{
		return mWorld;
	}

	void EventMessageAttributed::SetWorld(World* world)
	{
		mWorld = world;
	}

	EventMessageAttributed& EventMessageAttributed::operator=(const EventMessageAttributed& rhs)
	{
		if (this != &rhs)
		{
			//copying the actual values instead of the external signatures
			mWorld = rhs.mWorld; 
			mSubtype = rhs.mSubtype;

			CopyAuxillaryAttributes(rhs);
		}

		return *this;
	}

	EventMessageAttributed::EventMessageAttributed(const EventMessageAttributed& rhs)
	{
		*this = rhs;
	}
}