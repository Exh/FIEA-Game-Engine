#include "AssetSharedData.h"

namespace Test 
{
	RTTI_DEFINITIONS(AssetSharedData)

	AssetSharedData::AssetSharedData():
		mMaxDepth(0), mStartHandlerCallCount(0), mEndHandlerCallCount(0), mCharHandlerCallCount(0), mCharDataList(), mModelAttributeList(), mMeshAttributeList()
	{
	}

	XmlParseMaster::SharedData* AssetSharedData::Clone() const
	{
		AssetSharedData* clone = new AssetSharedData();
		return clone;
	}
}