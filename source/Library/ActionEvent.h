/**	@file ActionEvent.h
*	@brief Declaration of ActionEvent
*/

#pragma once
#include <string>
#include "Action.h"

namespace Library
{
	/**	@class ActionEvent
	*	@brief the class that raises EventAttributed events of a certain subtype
	*/
	class ActionEvent final : public Action
	{
		RTTI_DECLARATIONS(ActionEvent, Action)

	public:
		/**	@brief Constructor to default member */
		ActionEvent(const std::string& name="", const std::string& subtype="", std::uint32_t delay=0);

		/**	@brief Default destructor to release memory */
		virtual ~ActionEvent() = default;

		/**	@brief Raises an event, passes in the required information, and enqueues it 
		*	@param the state of the world
		*/
		virtual void Update(WorldState& worldState) override;

		/**	@brief Accessor for the subtype 
		*	@return the sub type of event
		*/
		const std::string& SubType() const;

		/**	@brief Setter for the sub type
		*	@param the new subtype
		*/
		void SetSubType(const std::string& subtype);

		/**	@brief Accessor for the delay in milliseconds
		*	@return the delay 
		*/
		std::uint32_t Delay() const;

		/**	@brief Setter for the message delay
		*	@param the new delay
		*/
		void SetDelay(std::uint32_t delay);

		ActionEvent& operator=(const ActionEvent& rhs) = delete;
		ActionEvent(const ActionEvent& rhs) = delete;

	protected:
		Datum* mSubtypeDatum; ///< cache of the subtype
		Datum* mDelayDatum; ///< cache of the delay
	};

	ACTION_FACTORY(ActionEvent)					
}