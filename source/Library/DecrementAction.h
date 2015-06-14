/**	@file DecrementAction.h
*	@brief Declarations of DecrementAction
*/

#pragma once
#include "Action.h"
#include "WorldState.h"

namespace Library
{
	/**	@class DecrementAction
	*	@brief Defines an action that decrements a static counter
	*/
	class DecrementAction final : public Action
	{
		RTTI_DECLARATIONS(DecrementAction, Action)

	public:
		/**	@brief Constructor that takes in an optional name for the action */
		DecrementAction(const std::string& name = "");

		/**	@brief Default destructor to release memory held by members */
		virtual ~DecrementAction() = default;
		
		/**	@brief Decrements the counter
		*	@param the state of the world
		*/
		virtual void Update(WorldState& worldState) override;

		static int mUpdateCount; ///< a counter to track how many times update was called

		//dis-allowing copying
		DecrementAction(const DecrementAction& rhs) = delete;
		DecrementAction& operator=(const DecrementAction& rhs) = delete;
	};

	ACTION_FACTORY(DecrementAction)
}
