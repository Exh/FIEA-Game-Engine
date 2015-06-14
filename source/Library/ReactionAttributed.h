/**	@file ReactionAttributed.h
*	@brief Declaration of Reaction Attributed class
*/

#pragma once
#include "Reaction.h"

namespace Library
{
	/**	@class ReactionAttributed
	*	@brief the class that receives the events set off by ActionEvent and performs certain behaviour
	*/
	class ReactionAttributed final : public Reaction
	{
		RTTI_DECLARATIONS(ReactionAttributed,Reaction)

	public:
		/**	@brief Constructor to default name and subscribe to event attributed events */
		ReactionAttributed(const std::string& name = "");

		/**	@brief Destructor to unsubscribe from publisher and release memory */
		virtual ~ReactionAttributed();

		/**	@brief Receives the message notification from the publisher
		*	@param the publisher of the event
		*/
		virtual void Notify(const EventPublisher& publisher) override;

		/**	@brief reaction update which does nothing, to suppress it from being treated as an action during world update
		*	@param the state of the world
		*/
		virtual void Update(WorldState& worldState) override;

		/**	@brief add a subtype that the reaction supports
		*	@param the subtype to add
		*/
		void AddSubtype(const std::string& subtype);

		/**	@brief return the subtypes the reaction supports
		*	@return datum of string with supported subtypes
		*/
		const Datum* SubTypes() const;

		/**	@brief Check if it supports a certain subtype
		*	@param the subtype to check
		*	@return true, if present, false, otherwise
		*/
		bool ContainsSubtype(const std::string& subtype) const;

		ReactionAttributed(const ReactionAttributed& rhs) = delete;
		ReactionAttributed& operator=(const ReactionAttributed& rhs) = delete;

	private:
		Datum* mSubType; ///< cache of the subtype from scope
	};

	ACTION_FACTORY(ReactionAttributed)
}

