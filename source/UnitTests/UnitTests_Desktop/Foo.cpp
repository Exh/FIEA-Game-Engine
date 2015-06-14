/**	@file Foo.cpp
*	@brief Implementation of Foo.h
*/
#include "Foo.h"

namespace Test
{
	RTTI_DEFINITIONS(Foo)

#pragma region Foo
	Foo::Foo(char data) 
		: mFooID(data), mBar(new Bar())
	{
	}

	Foo::~Foo()
	{
		delete mBar;
	}

	bool Foo::operator==(const Foo& rhs) const
	{
		return mFooID == rhs.mFooID;
	}

	char Foo::GetID() const
	{
		return mFooID;
	}

	Foo& Foo::operator=(const Foo& rhs)
	{
		if (this != &rhs)
		{
			mFooID = rhs.mFooID;
			*mBar = *rhs.mBar;
		}

		return *this;
	}

	Foo::Foo(const Foo& rhs) :Foo()
	{
		*this = rhs;
	}

	int Foo::GetBarID()
	{
		return mBar->id;
	}	
#pragma endregion

#pragma region Bar
	Foo::Bar::Bar(const int newId)
		:id(newId)
	{
	};

	Foo::Bar& Foo::Bar::operator=(const Bar& rhs)
	{
		if (this != &rhs)
		{
			id = rhs.id;
		}
		return *this;
	}

	Foo::Bar::Bar(const Bar& rhs) :Bar(rhs.id)
	{
	}
#pragma endregion
}