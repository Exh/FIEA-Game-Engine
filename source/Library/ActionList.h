/**	@file ActionList.h
*	@brief Declarations of ActionList
*/

#pragma once
#include "Action.h"

namespace Library
{
	/**	@class ActionList
	*	@brief Defines a list of actions
	*/
	class ActionList : public Action
	{
		RTTI_DECLARATIONS(ActionList, Action)

	public:
		/**	@brief Constructor that takes in an optional name for the action */
		ActionList(const std::string& name="");

		/**	@brief Default destructor to release memory held by members */
		virtual ~ActionList() = default;

		/**	@brief Calls update on its subactions by passing the state of the world	
		*	@param state of the world
		*/
		virtual void Update(WorldState& worldState) override;

		//dis-allowing copying
		ActionList(const ActionList& rhs) = delete;
		ActionList& operator=(const ActionList& rhs) = delete;
	};

	ACTION_FACTORY(ActionList)
}
