#include "MeshParseHelper.h"

#include "AssetSharedData.h"

namespace Test
{
	bool MeshParseHelper::StartElementHandler(SharedData* sharedData, const std::string& tagName, const HashMap<std::string, std::string>& attributes)
	{
		if (sharedData == nullptr)
		{
			return false;
		}

		if (!sharedData->Is("AssetSharedData"))
		{
			return false;
		}

		if (tagName != "mesh")
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
			data->mMeshAttributeList.PushBack(attributes);
		}

		return true;
	}

	bool MeshParseHelper::EndElementHandler(SharedData* sharedData, const std::string& tagName)
	{
		if (sharedData == nullptr)
		{
			return false;
		}

		if (!sharedData->Is("AssetSharedData"))
		{
			return false;
		}

		if (tagName != "mesh")
		{
			return false;
		}

		AssetSharedData* data = reinterpret_cast<AssetSharedData*>(sharedData);
		data->mEndHandlerCallCount++;

		return true;
	}

	IXmlParseHelper* MeshParseHelper::Create() const
	{
		MeshParseHelper* clone = new MeshParseHelper();
		return clone;
	}
}