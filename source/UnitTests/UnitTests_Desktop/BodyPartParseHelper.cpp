#include "BodyPartParseHelper.h"
#include "AssetSharedData.h"

namespace Test
{
	bool BodyPartParseHelper::StartElementHandler(SharedData* sharedData, const std::string& tagName, const HashMap<std::string, std::string>& attributes)
	{
		if (sharedData == nullptr)
		{
			return false;
		}

		if (!sharedData->Is("AssetSharedData"))
		{
			return false;
		}

		if (tagName != "bodyPart")
		{
			return false;
		}

		AssetSharedData* data = reinterpret_cast<AssetSharedData*>(sharedData);
		data->mStartHandlerCallCount++;

		if (data->Depth() > data->mMaxDepth)
		{
			data->mMaxDepth = data->Depth();
		}

		return true;
	}

	bool BodyPartParseHelper::EndElementHandler(SharedData* sharedData, const std::string& tagName)
	{
		if (sharedData == nullptr)
		{
			return false;
		}

		if (!sharedData->Is("AssetSharedData"))
		{
			return false;
		}

		if (tagName != "bodyPart")
		{
			return false;
		}

		AssetSharedData* data = reinterpret_cast<AssetSharedData*>(sharedData);
		data->mEndHandlerCallCount++;

		return true;
	}

	IXmlParseHelper *BodyPartParseHelper::Create() const
	{
		BodyPartParseHelper* clone = new BodyPartParseHelper();
		return clone;
	}

	bool BodyPartParseHelper::CharDataHandler(SharedData* sharedData, const std::string& innerText)
	{
		if (sharedData == nullptr)
		{
			return false;
		}

		if (!sharedData->Is("AssetSharedData"))
		{
			return false;
		}

		AssetSharedData* data = reinterpret_cast<AssetSharedData*>(sharedData);
		data->mCharHandlerCallCount++;
		data->mCharDataList.PushBack(innerText);

		return true;
	}
}