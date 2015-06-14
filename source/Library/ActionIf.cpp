/**	@file ActionIf.cpp
*	@brief Definitions of ActionIf
*/

#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(ActionIf)

	ActionIf::ActionIf(const std::string& name, std::int32_t condition)
		: Action(name), mThen(nullptr), mElse(nullptr), mCondition(nullptr)
	{
		INTERNAL_ATTRIBUTE("condition", Datum::DatumType::Integer, &condition, 1)
		INTERNAL_ATTRIBUTE("then", Datum::DatumType::Table, nullptr, 1)
		INTERNAL_ATTRIBUTE("else", Datum::DatumType::Table, nullptr, 1)

		Populate();

		//cache the attributes
		mCondition = Find("condition");
		mThen = (*this)["then"].GetTable();
		mElse = (*this)["else"].GetTable();
	}

	void ActionIf::Update(WorldState& worldState)
	{
		if ((*mCondition) == 1)
		{
			//cycle through all the actions in then and call update on it
			//in case the user decides to have several then's
			for (auto it = mThen->begin(); it != mThen->end(); ++it)
			{
				Action* action = (*it)->second.GetTable()->As<Action>();
				worldState.mAction = action;
				action->Update(worldState);
			}
		}
		else 
		{
			//similarly for else
			for (auto it = mElse->begin(); it != mElse->end(); ++it)
			{
				Action* action = (*it)->second.GetTable()->As<Action>();
				worldState.mAction = action;
				action->Update(worldState);
			}
		}
	}

	Scope* ActionIf::ThenClause() const
	{
		return mThen;
	}

	Scope* ActionIf::ElseClause() const
	{
		return mElse;
	}

	Datum* ActionIf::Condition() const
	{
		return mCondition;
	}
}