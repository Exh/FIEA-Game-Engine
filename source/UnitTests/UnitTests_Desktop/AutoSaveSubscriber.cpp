#include "AutoSaveSubscriber.h"

namespace Test
{
	AutoSaveSubscriber::AutoSaveSubscriber()
		:mMessageReceivedCount(0)
	{
	}

	void AutoSaveSubscriber::Notify(const Library::EventPublisher& publisher)
	{
		mMessageReceivedCount++;
		
	}
}