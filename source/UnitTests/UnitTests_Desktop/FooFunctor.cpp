/**	@file FooFunctor.cpp
*	@brief contains implementation of the Custom functor for vector, FooFunctor
*/
#include "FooFunctor.h"

namespace Test
{
	unsigned int FooFunctor::operator()(unsigned int size, unsigned int capacity) const
	{
		return capacity + 3;
	}
}