#pragma once
#include <string>
#include "RTTI.h"

using namespace Library;
namespace Test
{
	class AutoSaveArgs : public RTTI
	{
		RTTI_DECLARATIONS(AutoSaveArgs,RTTI)

	public:
		AutoSaveArgs(const std::string& saveLocation="");
		~AutoSaveArgs()=default;

		std::string mSaveLocation;
	};
}
