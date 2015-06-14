#include "PositionParseHelper.h"
#include "AssetSharedData.h"

namespace Test
{
	bool PositionParseHelper::StartElementHandler(SharedData* sharedData, const std::string& tagName, const HashMap<std::string, std::string>& attributes)
	{
		if (sharedData == nullptr)
		{
			return false;
		}

		AssetSharedData* data = sharedData->As<AssetSharedData>();
		if (data==nullptr)
		{
			return false;
		}

		if (tagName != "position" && tagName != "x" && tagName != "y" && tagName != "z")
		{
			return false;
		}

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

	bool PositionParseHelper::EndElementHandler(SharedData* sharedData, const std::string& tagName)
	{
		if (sharedData == nullptr)
		{
			return false;
		}

		AssetSharedData* data = sharedData->As<AssetSharedData>();
		if (data == nullptr)
		{
			return false;
		}

		if (tagName != "position" && tagName != "x" && tagName != "y" && tagName != "z")
		{
			return false;
		}

		data->mEndHandlerCallCount++;

		return true;
	}

	IXmlParseHelper* PositionParseHelper::Create() const
	{
		PositionParseHelper* clone = new PositionParseHelper();
		return clone;
	}

	bool PositionParseHelper::CharDataHandler(SharedData* sharedData, const std::string& innerText)
	{
		if (sharedData == nullptr)
		{
			return false;
		}

		AssetSharedData* data = sharedData->As<AssetSharedData>();
		if (data == nullptr)
		{
			return false;
		}

		data->mCharHandlerCallCount++;
		data->mCharDataList.PushBack(innerText);

		return true;
	}
}
