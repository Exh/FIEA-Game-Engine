#pragma once
#include "RTTI.h"
#include "Entity.h"
#include "ConcreteFactory.h"

using namespace Library;
namespace Test
{
	class Kaijuu : public Entity
	{
		RTTI_DECLARATIONS(Kaijuu, Entity)

	public:
		Kaijuu();
		~Kaijuu();
	};

	CONCRETE_FACTORY(Kaijuu,RTTI)
}

