/**	@file DecrementAction.cpp
*	@brief Definitions of DecrementAction
*/

#include "pch.h"
#include "DecrementAction.h"

namespace Library
{
	RTTI_DEFINITIONS(DecrementAction)

		int DecrementAction::mUpdateCount = 0;

	DecrementAction::DecrementAction(const std::string& name)
		:Action(name)
	{
	}

	void DecrementAction::Update(WorldState& worldState)
	{
		--mUpdateCount;
	}
}