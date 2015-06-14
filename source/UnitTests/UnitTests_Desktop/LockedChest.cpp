#include "LockedChest.h"

namespace Test
{
	RTTI_DEFINITIONS(LockedChest)

	LockedChest::LockedChest(const std::string& name)
		:Entity(name), mCallCount(0)
	{
	}

	void LockedChest::Update(WorldState& worldState)
	{
		Entity::Update(worldState);

		++mCallCount;
	}
}