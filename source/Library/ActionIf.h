/**	@file ActionIf.h
*	@brief Declarations of ActionIf
*/

#pragma once

namespace Library
{
	/**	@class ActionIf
	*	@brief Defines a conditional if-else action
	*/
	class ActionIf final : public Action
	{
		RTTI_DECLARATIONS(ActionIf, Action)

	public:
		/**	@brief Constructor that takes in an optional name for the action and a value for the condition */
		ActionIf(const std::string& name = "", std::int32_t condition = 1);

		/**	@brief Default destructor to release memory held by members */
		virtual ~ActionIf()=default;

		/**	@brief Perform a conditional option based on a condition
		*	@param state of the world
		*/
		virtual void Update(WorldState& worldState) override;

		/**	@brief Returns the scope containing the then clause of the conditional action 
		*	@return scope of the then clause
		*/
		Scope* ThenClause() const;

		/**	@brief Returns the scope containing the else clause of the conditional action
		*	@return scope of the else clause
		*/
		Scope* ElseClause() const;

		/**	@brief Returns the datum containing the condition of the conditional action
		*	@return datum of type integer for the condition
		*/
		Datum* Condition() const;

		//dis-allowing copying
		ActionIf(const ActionIf& rhs) = delete;
		ActionIf& operator=(const ActionIf& rhs) = delete;

	private:
		Scope* mThen;
		Scope* mElse;
		Datum* mCondition;
	};

	ACTION_FACTORY(ActionIf)
}
