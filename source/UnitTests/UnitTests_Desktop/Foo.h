/**	@file Foo.h
*	Contains declaration for user defined class for testing Slist
*/
#pragma once
#include "RTTI.h"

namespace Test
{
	/**	@class Foo
	*	User defined class to test SList
	*/
	class Foo final : public Library::RTTI
	{
		RTTI_DECLARATIONS(Foo, RTTI)

	public:
		/**	@class Bar
		*	@brief Inner class to check if memory leak occurs when we heap allocate inside Foo
		*/
		class Bar final
		{
		public:
			/** @brief Constructor to set value of id to 100 */
			Bar(const int newId = 100);
			/** @brief for deep copy */
			Bar& operator=(const Bar& rhs);
			/** @brief for deep copy */
			Bar(const Bar& rhs);
			int id; ///< arbitrary variable
		};

		/**	@brief Overloaded constructor to take in the value to initialise the ID to default of ' ' if not provided
		*	@param the value for ID
		*/
		Foo(const char data=' ');

		/**	@brief Destructor to clean up after the class during delete*/
		~Foo();

		/** @brief Overload == operator to facilitate comparison of Foo classes by comparing their IDs
		*	@param the Foo class to compare to
		*	@return true, if their IDs match
		*/
		bool operator==(const Foo& rhs) const;

		/**	@brief Accessor to expose the value of ID
		*	@return the value of ID
		*/
		char GetID() const;

		/**	@brief Deep copy of Foo
		*	@param The Foo to copy into this Foo
		*	@return reference to the copied Foo
		*/
		Foo& operator=(const Foo& rhs);

		/**	@brief Deep copy of Foo
		*	@param The Foo to copy into this Foo
		*/
		Foo(const Foo& rhs);

		/**	@brief Getter for Inner class Bar's id
		*	@return if id value in Bar
		*/
		int GetBarID();

	private:
		char mFooID; ///< an arbitrary variable just to test
		Bar* mBar; ///< arbitrary class to ensure no memory leak when heap allocated inside class
	};
}

