/**	@file EventMessageAttributed.h
*	@brief Declaration of EventMessageAttributed
*/

#pragma once
#include "Attributed.h"
#include "World.h"

namespace Library
{
	/**	@class EventMessageAttributed
	*	@brief the payload for action events
	*/
	class EventMessageAttributed final : public Attributed
	{
		RTTI_DECLARATIONS(EventMessageAttributed, Attributed)

	public:
		/**	@brief Constructor to initialise members */
		explicit EventMessageAttributed(const std::string& subtype="", World* world=nullptr);

		/**	@brief default destructor to release members */
		virtual ~EventMessageAttributed() = default;

		/**	@brief Getter for the subtype of payload
		*	@return the subtype
		*/
		const std::string& Subtype() const;

		/**	@brief Setter for the subtype of payload
		*	@param the new subtype
		*/
		void SetSubtype(const std::string& subtype);

		/**	@brief Getter for the world of payload
		*	@return the world
		*/
		World* GetWorld() const;

		/**	@brief Setter for the world of payload
		*	@param the new world
		*/
		void SetWorld(World* world);

		/**	@brief Deep copyies data and auxillary attributes
		*	@return the copy
		*	@param the thing to copy from
		*/
		EventMessageAttributed& operator=(const EventMessageAttributed& rhs);

		/**	@brief Deep copyies data and auxillary attributes
		*	@param the thing to copy from
		*/
		EventMessageAttributed(const EventMessageAttributed& rhs);

	private:
		std::string mSubtype;
		World* mWorld;
	};
}