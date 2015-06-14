/**	@file FooHash.cpp
*	@brief Implementation of FooHash
*/
#include "FooHash.h"

namespace Test
{
	/** @brief specialised functor for Foo */
	std::uint32_t FooHash::operator()(Foo key) const
	{
		int fooData = key.GetBarID()+key.GetID();
		return fooData;
	}

	/** @brief specialised functor for int */
	std::uint32_t FooHash::operator()(const int key) const
	{
		return key;
	}
};
