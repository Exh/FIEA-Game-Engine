/**	@file EnqueueActionEvent.h
*	Declaration of the EnqueueActionEvent class
*/

#pragma once
#include "Action.h"

using namespace Library;
namespace Test
{
	/**	@class 
	*	@brief
	*/
	class EnqueueActionEvent final : public Action
	{
		RTTI_DECLARATIONS(EnqueueActionEvent, Action)

	public:

		/**	@brief Constructor to default name and subscribe to event attributed events */
		EnqueueActionEvent(const std::string& name = "");

		/**	@brief Constructor to default name and subscribe to event attributed events */
		virtual ~EnqueueActionEvent()=default;

		/**	@brief Receives the message notification from the publisher
		*	@param the publisher of the event
		*/
		virtual void Update(WorldState& worldState) override;

		//disallowing copying
		EnqueueActionEvent(const EnqueueActionEvent& rhs) = delete;
		EnqueueActionEvent& operator=(const EnqueueActionEvent& rhs) = delete;

		static int UpdateCount; //count for testing
	};

	ACTION_FACTORY(EnqueueActionEvent)
}
