#include "ModelParseHelper.h"
#include "AssetSharedData.h"

namespace Test
{
	bool ModelParseHelper::StartElementHandler(SharedData* sharedData, const std::string& tagName, const HashMap<std::string, std::string>& attributes)
	{
		if (sharedData == nullptr)
		{
			return false;
		}

		if (!sharedData->Is("AssetSharedData"))
		{
			return false;
		}

		if (tagName != "model")
		{
			return false;
		}

		AssetSharedData* data = reinterpret_cast<AssetSharedData*>(sharedData);
		data->mStartHandlerCallCount++;

		if (data->Depth() > data->mMaxDepth)
		{
			data->mMaxDepth = data->Depth();
		}

		if (attributes.Size() > 0)
		{
			data->mModelAttributeList.PushBack(attributes);
		}

		return true;
	}

	bool ModelParseHelper::EndElementHandler(SharedData* sharedData, const std::string& tagName)
	{
		if (sharedData == nullptr)
		{
			return false;
		}

		if (!sharedData->Is("AssetSharedData"))
		{
			return false;
		}

		if (tagName != "model")
		{
			return false;
		}

		AssetSharedData* data = reinterpret_cast<AssetSharedData*>(sharedData);
		data->mEndHandlerCallCount++;

		return true;
	}

	IXmlParseHelper* ModelParseHelper::Create() const
	{
		ModelParseHelper* clone = new ModelParseHelper();
		return clone;
	}
}
