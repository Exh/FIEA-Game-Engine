#include "AutoSaveArgs.h"

namespace Test
{
	RTTI_DEFINITIONS(AutoSaveArgs)

	AutoSaveArgs::AutoSaveArgs(const std::string& saveLocation)
		:mSaveLocation(saveLocation)
	{
	}
}
