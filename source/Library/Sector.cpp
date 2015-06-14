/**	@file Sector.cpp
*	@brief Contains defintions of Sector
*/
#include "pch.h"
#include "Sector.h"

namespace Library
{
	RTTI_DEFINITIONS(Sector)

	Sector::Sector(const std::string& name)
		:mWorld(nullptr), mName(name)
	{
		EXTERNAL_ATTRIBUTE("name", Datum::DatumType::String, &mName, 1)
		INTERNAL_ATTRIBUTE("entities", Datum::DatumType::Table, nullptr, 1) //defaulting to new scope
		INTERNAL_ATTRIBUTE("actions", Datum::DatumType::Table, nullptr, 1)

		Populate();

		mEntities = (*this)["entities"].GetTable(); //caching this value to reduce lookups
		mActions = (*this)["actions"].GetTable();
	}

	const std::string& Sector::Name() const
	{
		return mName;
	}

	Scope* Sector::Entities() const
	{
		return mEntities;
	}

	Scope* Sector::Actions() const
	{
		return mActions;
	}

	Entity* Sector::CreateEntity(const std::string& className, const std::string& instanceName)
	{
		if (Factory<RTTI>::ContainsFactory(className))
		{
			Entity* newEntity = Factory<RTTI>::Create(className)->As<Entity>();

			if (newEntity != nullptr)
			{
				newEntity->mName = instanceName;
				newEntity->SetSector(*this);

				return newEntity;
			}
		}

		return nullptr;
	}

	void Sector::SetWorld(World& world)
	{
		mWorld = &world;

		assert(mWorld->Sectors() != nullptr);
			
		mWorld->Sectors()->Adopt(*this, mName);
	}

	World* Sector::GetWorld() const
	{
		return mWorld;
	}

	void Sector::Update(WorldState& worldState)
	{
		//update sector actions
		for (auto actionIt = mActions->begin(); actionIt != mActions->end(); ++actionIt)
		{
			auto& datum = (*(actionIt))->second;

			for (std::uint32_t i = 0; i < datum.Size(); ++i)
			{
				auto* action = (datum.GetTable(i))->As<Action>();

				if (action != nullptr)
				{
					worldState.mAction = action;
					action->Update(worldState);
				}
			}
		}

		//update entities
		for (auto scopeIt = mEntities->begin(); scopeIt != mEntities->end(); ++scopeIt)
		{
			auto& datum = (*(scopeIt))->second;

			for (std::uint32_t i = 0; i < datum.Size(); ++i)
			{
				auto* entity = (datum.GetTable(i))->As<Entity>();

				if (entity != nullptr)
				{
					worldState.mEntity = entity; //doing this here so that when user derives from entity, they wont forget to set this
					entity->Update(worldState);
				}
			}
		}
	}

	Action* Sector::CreateAction(const std::string& className, const std::string& instanceName)
	{
		if (Factory<Action>::ContainsFactory(className))
		{
			Action* newAction = Factory<Action>::Create(className)->As<Action>();

			if (newAction != nullptr)
			{
				newAction->mName = instanceName;
				newAction->SetSector(*this);

				return newAction;
			}
		}

		return nullptr;
	}
}