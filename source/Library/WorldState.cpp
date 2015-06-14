/**	@file WorldState.cpp
*	@brief Definitions of WorldState
*/

#include "pch.h"
#include "WorldState.h"

namespace Library
{
	WorldState::WorldState()
		: mGameTime(nullptr), mWorld(nullptr), mSector(nullptr), mEntity(nullptr), mAction(nullptr)
	{
	}

	WorldState& WorldState::operator=(const WorldState& rhs)
	{
		if (this != &rhs)
		{
			mWorld = rhs.mWorld;
			mSector = rhs.mSector;
			mEntity = rhs.mEntity;
			mGameTime = rhs.mGameTime;
			mAction = rhs.mAction;
		}

		return *this;
	}

	WorldState::WorldState(const WorldState& rhs)
	{
		*this = rhs;
	}

	bool WorldState::operator==(const WorldState& rhs)
	{
		return (mGameTime == rhs.mGameTime && mWorld == rhs.mWorld && mSector == rhs.mSector && mEntity == rhs.mEntity && mAction==rhs.mAction);
	}

	bool WorldState::operator!=(const WorldState& rhs)
	{
		return !(operator==(rhs));
	}
}