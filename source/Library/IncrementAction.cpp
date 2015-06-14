/**	@file IncrementAction.cpp
*	@brief Definitions of IncrementAction
*/

#include "pch.h"
#include "IncrementAction.h"

namespace Library
{
	RTTI_DEFINITIONS(IncrementAction)

	int IncrementAction::mUpdateCount = 0;

	IncrementAction::IncrementAction(const std::string& name)
		:Action(name)
	{
	}

	void IncrementAction::Update(WorldState& worldState)
	{
		++mUpdateCount;
	}
}