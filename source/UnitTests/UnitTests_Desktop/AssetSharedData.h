#pragma once
#include "XmlParseMaster.h"
#include "Slist.h"
#include "hashmap.h"

using namespace Library;

namespace Test
{
	class AssetSharedData final : public XmlParseMaster::SharedData
	{
		RTTI_DECLARATIONS(AssetSharedData, XmlParseMaster::SharedData)

	public:
		AssetSharedData();
		virtual ~AssetSharedData() = default;
		
		virtual XmlParseMaster::SharedData* Clone() const;

		//debug data - public for testing
		std::uint32_t mMaxDepth;
		
		std::uint32_t mStartHandlerCallCount;
		std::uint32_t mEndHandlerCallCount;
		std::uint32_t mCharHandlerCallCount;

		SList<std::string> mCharDataList; //holds list of data encountered while handling char data
		SList<HashMap<std::string, std::string>> mModelAttributeList; //list of attributes while handling model tag
		SList<HashMap<std::string, std::string>> mMeshAttributeList; //list of attributes when handling mesh tag
	};
}

