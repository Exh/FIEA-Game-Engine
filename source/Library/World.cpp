/**	@file World.cpp
*	@brief Contains defintions of World
*/
#include "pch.h"
#include "World.h"

namespace Library
{
	RTTI_DEFINITIONS(World)

	World::World(const std::string& name)
		:mName(name)
	{
		EXTERNAL_ATTRIBUTE("name", Datum::DatumType::String, &mName, 1)
		INTERNAL_ATTRIBUTE("sectors", Datum::DatumType::Table, nullptr, 1) //defaulting to new scope
		INTERNAL_ATTRIBUTE("actions", Datum::DatumType::Table, nullptr, 1)

		Populate();

		mSectors = (*this)["sectors"].GetTable(); //caching this to reduce lookups
		mActions = (*this)["actions"].GetTable();

		mWorldState.mWorld = this;
		mWorldState.mGameTime = &mGameTime;
	}

	Scope* World::Sectors() const
	{
		return mSectors;
	}

	Scope* World::Actions() const
	{
		return mActions;
	}

	Sector* World::CreateSector(const std::string& instanceName)
	{
		if (Factory<RTTI>::ContainsFactory("Sector"))
		{
			Sector* newSector = Factory<RTTI>::Create("Sector")->As<Sector>();

			if (newSector != nullptr)
			{
				newSector->mName = instanceName;
				newSector->SetWorld(*this);
				
				return newSector;
			}
		}

		return nullptr;
	}

	void World::Update()
	{
		for (auto actionIt = mActions->begin(); actionIt != mActions->end(); ++actionIt)
		{
			auto& datum = (*(actionIt))->second;

			for (std::uint32_t i = 0; i < datum.Size(); ++i)
			{
				auto* action = (datum.GetTable(i))->As<Action>();

				if (action != nullptr)
				{
					mWorldState.mAction = action;
					action->Update(mWorldState);
				}
			}
		}

		//update the event queue
		mEventQueue.Update(mGameTime);

		for (auto scopeIt = mSectors->begin(); scopeIt != mSectors->end();++scopeIt)
		{
			auto& datum = (*(scopeIt))->second;

			for (std::uint32_t i = 0; i < datum.Size(); ++i)
			{
				auto* sector = (datum.GetTable(i))->As<Sector>();

				if (sector != nullptr)
				{
					mWorldState.mSector = sector; //doing this in here so when we derive entity, user wont forget to update this
					sector->Update(mWorldState);
				}
			}
		}
	}

	const std::string& World::Name() const
	{
		return mName;
	}

	void World::SetName(const std::string& name)
	{
		mName = name;
	}

	Action* World::CreateAction(const std::string& className, const std::string& instanceName)
	{
		if (Factory<Action>::ContainsFactory(className))
		{
			Action* newAction = Factory<Action>::Create(className)->As<Action>();

			if (newAction != nullptr)
			{
				newAction->mName = instanceName;
				newAction->SetWorld(*this);

				return newAction;
			}
		}

		return nullptr;
	}

	const WorldState& World::GetWorldState() const
	{
		return mWorldState;
	}

	const EventQueue& World::GetEventQueue() const
	{
		return mEventQueue;
	}

	const GameTime& World::GetGameTime() const
	{
		return mGameTime;
	}
}