#include "pch.h"
#include "Reaction.h"

namespace Library
{
	RTTI_DEFINITIONS(Reaction)

	Reaction::Reaction(const std::string& name)
	: ActionList(name)
	{
	}

	void Reaction::Update(WorldState& worldState)
	{
	}
}