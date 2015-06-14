/**	@file DefaultVectorFunctor.cpp
*	@brief Implementation for the default reserve scheme for Vector
*/

#include "pch.h"
#include "DefaultVectorFunctor.h"

namespace Library
{
	DefaultVectorFunctor::DefaultVectorFunctor()
	{
	}

	DefaultVectorFunctor::~DefaultVectorFunctor()
	{
	}

	//capacity always doubles
	unsigned int DefaultVectorFunctor::operator()(unsigned int size, unsigned int capacity) const
	{
		if (capacity == 0)
		{
			return 1;
		}

		return capacity * 2;
	}
}
