/**	@file TableSharedData.h
*	@brief Declaration of class TableSharedData
*/

#pragma once
#include "stack.h"
#include "hashmap.h"
#include "XmlParseMaster.h"

namespace Library
{
	/**	@class TableSharedData
	*	@brief Specialised shared data for table parsing
	*/
	class TableSharedData final : public XmlParseMaster::SharedData
	{
		RTTI_DECLARATIONS(TableSharedData, XmlParseMaster::SharedData)

	public:
		/**	@brief Constructor that takes in a scope, optionally. If the scope is not set before parse, it will result in a std::exception 
		*	@param The scope that should be populated during the parse
		*/
		TableSharedData(Scope* parentScope = nullptr);
		
		/**	@brief Virtual destructor to clear the data if it is a clone */
		virtual ~TableSharedData();

		/**	@brief Method to create a deep copy of the shared data. It is upto to the client to delete the clone. 
		*	@return Copy of the current instance
		*/
		virtual SharedData* Clone() const override;
		
		/**	@brief Accessor for the scope currently being populated by the system
		*	@return the scope being populated
		*/
		Scope* GetParsedScope() const;
		
		/**	@brief Mutator to set the scope currently being populated by the system
		*	@param address of the scope that should be populated
		*/
		void SetCurrentScope(Scope* scope);

		/**	@brief Returns if the current instance is a clone
		*	@return true, if it is a clone, false otherwise
		*/
		bool IsClone() const;
		
		/**	@brief Initialise the shared data to the original state */
		virtual void Initialise() override;

		Stack<std::string> mContextStack; ///< Stack that maintains the state of the parsing system, public for easier access
	private:
		Scope* mParsedScope;
		bool mIsClone;
	};
}
