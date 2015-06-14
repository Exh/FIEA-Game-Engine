/**	@file FooHash.h
*	@brief Definition of FooHash class
*/
#pragma once

#include <cstdint>
#include "Foo.h"

namespace Test
{
	/**	@class FooHash
	*	@brief Hash Functor for Foo class
	*/
	class FooHash final
	{
	public:
		/**	@brief Hash function for Foo keys
		*	@param key
		*	@return hash value
		*/
		std::uint32_t operator()(Foo key) const;

		/**	@brief Hash function for int keys
		*	@param key
		*	@return hash value
		*/
		std::uint32_t operator()(const int key) const;

	};
};

