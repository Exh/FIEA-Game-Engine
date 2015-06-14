/**	@file IncrementAction.h
*	@brief Declarations of IncrementAction
*/
#pragma once
#include "Action.h"
#include "WorldState.h"

namespace Library
{
	/**	@class IncrementAction
	*	@brief Defines an action that increments a static counter
	*/
	class IncrementAction final : public Action
	{
		RTTI_DECLARATIONS(IncrementAction, Action)

	public:
		/**	@brief Constructor that takes in an optional name for the action */
		IncrementAction(const std::string& name = "");

		/**	@brief Default destructor to release memory held by members */
		virtual ~IncrementAction()=default;

		/**	@brief Increments the counter
		*	@param the state of the world
		*/
		virtual void Update(WorldState& worldState) override;

		static int mUpdateCount; ///< a counter to track how many times update was called

		//dis-allowing copying
		IncrementAction(const IncrementAction& rhs) = delete;
		IncrementAction& operator=(const IncrementAction& rhs) = delete;
	};

	ACTION_FACTORY(IncrementAction)
}
