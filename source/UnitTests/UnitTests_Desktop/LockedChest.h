#pragma once
#include "Entity.h"
#include "RTTI.h"
#include "ConcreteFactory.h"

using namespace Library;

namespace Test
{
	class LockedChest final : public Entity
	{
		RTTI_DECLARATIONS(LockedChest, Entity)

	public:
		std::uint32_t mCallCount; //to store the number of times update was called

		LockedChest(const std::string& name="");
		virtual ~LockedChest()=default;

		void Update(WorldState& worldState);
	};

	CONCRETE_FACTORY(LockedChest, RTTI)
}
