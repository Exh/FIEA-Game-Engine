/**	@file ActionList.cpp
*	@brief Definitions of ActionList
*/

#include "pch.h"
#include "ActionList.h"

namespace Library
{
	RTTI_DEFINITIONS(ActionList)

	ActionList::ActionList(const std::string& name)
		:Action(name)
	{
	}

	void ActionList::Update(WorldState& worldState)
	{
		//cycle through subactions and call update on them
		for (auto actionIt = mSubActions->begin(); actionIt != mSubActions->end(); ++actionIt)
		{
			auto& datum = (*(actionIt))->second;

			for (std::uint32_t i = 0; i < datum.Size(); ++i)
			{
				auto* action = (datum.GetTable(i))->As<Action>();

				if (action != nullptr)
				{
					worldState.mAction = action; //update the state to the action to be called first
					action->Update(worldState);
				}
			}
		}
	}
}