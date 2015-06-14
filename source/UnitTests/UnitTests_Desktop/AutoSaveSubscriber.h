#pragma once
#include "EventSubscriber.h"
#include "EventPublisher.h"
#include <string>

namespace Test
{
	class AutoSaveSubscriber : public Library::EventSubscriber
	{
	public:
		AutoSaveSubscriber();
		virtual ~AutoSaveSubscriber()=default;

		virtual void Notify(const Library::EventPublisher& publisher) override;

		int mMessageReceivedCount;
	};
}
