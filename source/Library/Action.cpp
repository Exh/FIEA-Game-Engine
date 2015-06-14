/**	@file Action.cpp
*	@brief Definitions of Action
*/
#include "pch.h"
#include "Action.h"

namespace Library
{
	RTTI_DEFINITIONS(Action)

	Action::Action(const std::string& name)
		: mName(name), mWorld(nullptr), mEntity(nullptr), mSector(nullptr), mAction(nullptr), mSubActions(nullptr)
	{
		//INIT_SIGNATURES

		EXTERNAL_ATTRIBUTE("name", Datum::DatumType::String, &mName, 1)
		INTERNAL_ATTRIBUTE("sub-actions", Datum::DatumType::Table, nullptr, 1) //defaulting to new scope

		Populate();

		mSubActions = (*this)["sub-actions"].GetTable(); //caching to reduce lookups
	}

	const std::string& Action::Name() const
	{
		return mName;
	}

	void Action::SetEntity(Entity& entity)
	{
		mSector = nullptr;
		mWorld = nullptr;
		mAction = nullptr;
		mEntity = &entity;

		assert(mEntity->Actions() != nullptr);

		mEntity->Actions()->Adopt(*this, mName);
	}

	void Action::SetWorld(World& world)
	{
		mSector = nullptr;
		mEntity = nullptr;
		mAction = nullptr;
		mWorld = &world;

		assert(mWorld->Actions() != nullptr);

		mWorld->Actions()->Adopt(*this, mName);
	}

	void Action::SetSector(Sector& sector)
	{
		mWorld = nullptr;
		mEntity = nullptr;
		mAction = nullptr;
		mSector = &sector;

		assert(mSector->Actions() != nullptr);

		mSector->Actions()->Adopt(*this, mName);
	}

	void Action::SetAction(Action& action)
	{
		mSector = nullptr;
		mEntity = nullptr;
		mWorld = nullptr;
		mAction = &action;

		assert(mAction->SubActions() != nullptr);

		mAction->SubActions()->Adopt(*this, mName);	
	}

	Scope* Action::SubActions() const
	{
		return mSubActions;
	}

	Entity* Action::GetEntity() const
	{
		return mEntity;
	}

	Action* Action::GetAction() const
	{
		return mAction;
	}

	Sector* Action::GetSector() const
	{
		return mSector;
	}

	World* Action::GetWorld() const
	{
		return mWorld;
	}

	Action* Action::CreateSubAction(const std::string& className, const std::string& instanceName)
	{
		if (Factory<Action>::ContainsFactory(className))
		{
			Action* newAction = Factory<Action>::Create(className)->As<Action>();

			if (newAction != nullptr)
			{
				newAction->mName = instanceName;
				newAction->SetAction(*this);

				return newAction;
			}
		}

		return nullptr;
	}
}