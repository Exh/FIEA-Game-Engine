/**	@file Entity.cpp
*	@brief Contains definitions of Entity
*/
#include "pch.h"
#include "Entity.h"
#include "Action.h"

namespace Library
{
	RTTI_DEFINITIONS(Entity)

	Entity::Entity(const std::string& name)
		: mSector(nullptr), mName(name)
	{
		EXTERNAL_ATTRIBUTE("name", Datum::DatumType::String, &mName, 1)
		INTERNAL_ATTRIBUTE("actions", Datum::DatumType::Table, nullptr, 1) //defaulting to new scope

		Populate();

		mActions = (*this)["actions"].GetTable(); //caching to reduce lookups
	}

	const std::string& Entity::Name() const
	{
		return mName;
	}

	Sector* Entity::GetSector() const
	{
		return mSector;
	}

	void Entity::SetSector(Sector& sector)
	{
		mSector = &sector;

		assert(mSector->Entities() != nullptr);

		mSector->Entities()->Adopt(*this, mName);
		
	}

	Scope* Entity::Actions() const
	{
		return mActions;
	}

	void Entity::Update(WorldState& worldState)
	{
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
	}

	Action* Entity::CreateAction(const std::string& className, const std::string& instanceName)
	{
		if (Factory<Action>::ContainsFactory(className))
		{
			Action* newAction = Factory<Action>::Create(className)->As<Action>();

			if (newAction != nullptr)
			{
				newAction->mName = instanceName;
				newAction->SetEntity(*this);

				return newAction;
			}
		}

		return nullptr;
	}
}