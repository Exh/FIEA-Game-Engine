/**	@file TableSharedData.cpp
*	@brief Definitions of TableSharedData
*/

#include "pch.h"
#include "TableSharedData.h"

namespace Library
{
	RTTI_DEFINITIONS(TableSharedData)

	TableSharedData::TableSharedData(Scope* parentScope) :
		mParsedScope(parentScope), mIsClone(false)
	{
	}

	TableSharedData::~TableSharedData()
	{
		if (mIsClone)
		{
			delete mParsedScope;
		}

		mParsedScope = nullptr;
	}

	XmlParseMaster::SharedData* TableSharedData::Clone() const
	{
		TableSharedData* newData = new TableSharedData();
		newData->mIsClone = true;

		if (mParsedScope != nullptr)
		{
			newData->mParsedScope = new Scope(*mParsedScope);
		}
		else
		{
			newData->mParsedScope = nullptr;
		}

		return newData;
	}

	bool TableSharedData::IsClone() const
	{
		return mIsClone;
	}

	Scope* TableSharedData::GetParsedScope() const
	{
		return mParsedScope;
	}

	void TableSharedData::SetCurrentScope(Scope* scope)
	{
		if (scope != nullptr)
		{
			mParsedScope = scope;
		}
	}

	void TableSharedData::Initialise()
	{
		XmlParseMaster::SharedData::Initialise();

		mContextStack.Clear();
	}
}