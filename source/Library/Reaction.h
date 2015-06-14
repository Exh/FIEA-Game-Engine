/**	@file Reaction.h
*	@brief Declaration of Reaction
*/
#pragma once
#include "ActionList.h"
#include "EventSubscriber.h"

namespace Library
{
	/**	@class Reaction
	*	@brief iinterface for Reaction events
	*/
	class Reaction : public ActionList, public EventSubscriber
	{
		RTTI_DECLARATIONS(Reaction, ActionList)

	public:
		/**	@brief constructor to initalise members */
		Reaction(const std::string& name = "");

		/**	@brief destructor to free members*/
		virtual ~Reaction() = default;

		/**	@brief updates the reaction - does nothing. to suppress reaction from being treated as an action during world update
		*	@param the state of the world
		*/
		void Update(WorldState& worldState) override;

		//not allowing copying
		Reaction& operator=(const Reaction& rhs) = delete;
		Reaction(const Reaction& rhs) = delete;
	};
}

