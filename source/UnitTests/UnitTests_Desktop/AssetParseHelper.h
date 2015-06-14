#pragma once
#include "IXmlParseHelper.h"

using namespace Library;

namespace Test
{
	/** Supported xml vocabulary <asset></asset> */
	class AssetParseHelper final : public IXmlParseHelper
	{
	public:
		AssetParseHelper() = default;
		virtual ~AssetParseHelper()=default;

		virtual bool StartElementHandler(SharedData* sharedData, const std::string& tagName, const HashMap<std::string, std::string>& attributes);
		virtual bool EndElementHandler(SharedData* sharedData, const std::string& tagName);
		virtual IXmlParseHelper* Create() const override;
	};
}
