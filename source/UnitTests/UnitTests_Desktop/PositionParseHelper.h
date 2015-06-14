#pragma once
#include "IXmlParseHelper.h"

using namespace Library;

namespace Test
{
	/** Supported xml vocabulary <position> <x></x> <y></y> <z></z> </position> */
	class PositionParseHelper final : public IXmlParseHelper
	{
	public:
		PositionParseHelper()=default;
		virtual ~PositionParseHelper()=default;

		virtual bool StartElementHandler(SharedData* sharedData, const std::string& tagName, const HashMap<std::string, std::string>& attributes) override;
		virtual bool EndElementHandler(SharedData* sharedData, const std::string& tagName) override;
		virtual bool CharDataHandler(SharedData* sharedData, const std::string& innerText) override;

		virtual IXmlParseHelper* Create() const override;
	};
}
