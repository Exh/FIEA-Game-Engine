#pragma once
#include "Event.h"
#include "AutoSaveArgs.h"
#include "RTTI.h"

using namespace Library;
using namespace Test;

namespace Test
{
	class AutoSaveEvent : public Event<AutoSaveArgs>
	{
		RTTI_DECLARATIONS(AutoSaveEvent, Event<AutoSaveArgs>)

	public:
		AutoSaveEvent();
		virtual ~AutoSaveEvent() =default;
	};
}
