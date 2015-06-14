#pragma once
#include "RTTI.h"
#include "Entity.h"
#include "ConcreteFactory.h"

using namespace Library;

namespace Test
{
	class Shujinko final : public Entity
	{
		RTTI_DECLARATIONS(Shujinko, Entity)
	public:
		Shujinko();
		~Shujinko();
	};

	CONCRETE_FACTORY(Shujinko, RTTI)
}
