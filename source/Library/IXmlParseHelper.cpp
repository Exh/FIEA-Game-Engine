#include "pch.h"
#include "IXmlParseHelper.h"

namespace Library
{
	void IXmlParseHelper::Initialize()
	{
	}

	bool IXmlParseHelper::StartElementHandler(SharedData* sharedData, const std::string& tagName, const HashMap<std::string, std::string>& attributes)
	{
		return false;
	}

	bool IXmlParseHelper::EndElementHandler(SharedData* sharedData, const std::string& tagName)
	{
		return false;
	}

	bool IXmlParseHelper::CharDataHandler(SharedData* sharedData, const std::string& innerText)
	{
		return false;
	}

	bool IXmlParseHelper::operator==(const IXmlParseHelper& rhs) const
	{
		return (this==&rhs);
	}

	bool IXmlParseHelper::operator!=(const IXmlParseHelper& rhs) const
	{
		return !(*this == rhs);
	}
}