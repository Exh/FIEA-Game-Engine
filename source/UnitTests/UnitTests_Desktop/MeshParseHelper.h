#pragma once
#include "IXmlParseHelper.h"

using namespace Library;

namespace Test
{
	/** Supported xml vocabulary <mesh name="" collider="" /> */
	class MeshParseHelper final : public IXmlParseHelper
	{
	public:
		MeshParseHelper()=default;
		virtual ~MeshParseHelper()=default;

		virtual bool StartElementHandler(SharedData* sharedData, const std::string& tagName, const HashMap<std::string, std::string>& attributes) override;
		virtual bool EndElementHandler(SharedData* sharedData, const std::string& tagName) override;
		virtual IXmlParseHelper* Create() const override;
	};
}

