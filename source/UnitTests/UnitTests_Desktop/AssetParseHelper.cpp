#include "AssetParseHelper.h"
#include "AssetSharedData.h"

namespace Test
{
	bool AssetParseHelper::StartElementHandler(SharedData* sharedData, const std::string& tagName, const HashMap<std::string, std::string>& attributes)
	{
		if (sharedData == nullptr)
		{
			return false;
		}

		if (!sharedData->Is("AssetSharedData"))
		{
			return false;
		}

		if (tagName != "asset")
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

	bool AssetParseHelper::EndElementHandler(SharedData* sharedData, const std::string& tagName)
	{
		if (sharedData == nullptr)
		{
			return false;
		}

		if (!sharedData->Is("AssetSharedData"))
		{
			return false;
		}

		if (tagName != "asset")
		{
			return false;
		}

		AssetSharedData* data = reinterpret_cast<AssetSharedData*>(sharedData);
		data->mEndHandlerCallCount++;

		return true;
	}

	IXmlParseHelper* AssetParseHelper::Create() const
	{
		AssetParseHelper* clone = new AssetParseHelper();
		return clone;
	}
}