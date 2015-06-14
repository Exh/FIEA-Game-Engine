#pragma once
#include "IXmlParseHelper.h"

using namespace Library;

namespace Test
{
	/**	Supported xml vocabulary <bodyPart part="" /> or <bodyPart></bodyPart> */
	class BodyPartParseHelper final : public IXmlParseHelper
	{
	public:
		BodyPartParseHelper()=default;
		virtual ~BodyPartParseHelper()=default;

		virtual bool StartElementHandler(SharedData* sharedData, const std::string& tagName, const HashMap<std::string, std::string>& attributes) override;
		virtual bool EndElementHandler(SharedData* sharedData, const std::string& tagName) override;
		virtual bool CharDataHandler(SharedData* sharedData, const std::string& innerText) override;

		virtual IXmlParseHelper* Create() const override;
	};
}
