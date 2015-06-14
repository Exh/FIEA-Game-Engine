/**	@file Scope.h
*	@brief Declaration of Scope
*/
#pragma once

#include "hashmap.h"
#include "vector.h"
#include "Datum.h"
#include "RTTI.h"
#include <string>
#include <cstdint>
#include <climits>

namespace Library
{
	/**	@class Scope
	*	@brief Stores name datum pairs emulating scope in common programming languages
	*/
	class Scope :public RTTI
	{
		RTTI_DECLARATIONS(Scope, RTTI)

	public:
		typedef std::pair<std::string, Datum> PairType;
		typedef Vector<PairType*>::Iterator Iterator;

		/** @brief Constructor to initialise the hashmap and vector to have the capacity mentioned and sets parent to null */
		explicit Scope(std::uint32_t initialCapacity=10);

		/**	@brief Clears the hashmap and order vector */
		 virtual ~Scope();

		/**	@brief Method to clear and delete all internal scopes and the order vector */
		void Clear();
		
		/**	@brief Copy constructor to deep copy the scopes
		*	@param the scope to copy from
		*/
		Scope(const Scope& rhs);

		/**	@brief Method to deep copy the scopes
		*	@param the scope to copy from
		*	@return reference to the copied scope
		*/
		Scope& operator=(const Scope& rhs);

		/**	@brief Find the datum associated with the name in the scope
		*	@param the name of the datum to find
		*	@return the found datum, or nullptr if not found
		*/
		Datum* Find(const std::string& name) const;

		/**	@brief Search for the datum associated with the name in the current scope or its ancestors
		*	@param the name of the datum to find
		*	@param the address of the the scope the datum is in
		*	@return the found datum, or nullptr if not found
		*/
		Datum* Search(const std::string& name, Scope** foundScope = nullptr) const;

		/**	@brief Create a new datum in the scope with the name or return the existing one. 
		* Note: Do not use this for scope as it will not set the parents for child scopes. This will break hierarchy and possibly leak memory, if used. 
		* Use AppendScope instead.
		*	@param the name of the datum to create and return
		*	@return the reference to the created datum
		*	@throws std::exception, if the name is empty
		*/
		Datum& Append(const std::string& name);

		/**	@brief Create a new datum of type Table or add to the existing one
		*	@param the name of the datum to add to
		*	@return the address of the created scope
		*	@throws std::exception, if the name is empty, or if the existing datum is not of type Table or is external
		*/
		Scope* AppendScope(const std::string& name);

		Scope* AppendScopeAt(const std::string& name, std::uint32_t index = UINT32_MAX);

		/**	@brief Add the child onto the datum associated with the name at the specified index. A new datum is created if not present. 
		* The child is added at the end of the array or in an empty spot if the index is invalid.
		*	@param the scope to add to this scope
		*	@param the name of the datum
		*	@param the index to add in
		*	@throws std::exception, if the child is null
		*/
		void Adopt(Scope& child, const std::string& childName, std::uint32_t index = UINT32_MAX);

		/**	@brief Return the parent of this scope
		*	@return the address of the parent scope if present or nullptr
		*/
		Scope* GetParent() const;

		/**	@brief Shorthand for Append */
		Datum& operator[](const std::string& name);

		/**	@brief Get the datum at the specified index. Order is determined by the order in which the datums are added to the scope
		*	@param the index to retrieve
		*	@return the refernce to the datum at that index
		*	@throws std::out_of_range if the index is invalid
		*/
		Datum& operator[](std::uint32_t index);

		/**	@brief Compare if the two scopes have the same datums with same name and same data
		*	@param the scope to compare
		*	@return true if the two scopes are equivalent, false otherwise
		*/
		bool operator==(const Scope& rhs) const;

		/**	@brief Compare if the two scopes are not the same
		*	@param the scope to compare
		*	@return false if the two scopes are equivalent, true otherwise
		*/
		bool operator!=(const Scope& rhs) const;

		/**	@brief find the name of the datum the scope resides in
		*	@param the scope to find
		*	@param the name of the associated datum, or empty string of not found
		*	@return true if the scope was found, false otherwise
		*	@throws std::exception if the scope is null
		*/
		bool FindName(const Scope& data, std::string& foundName) const;
		
		/**	@brief Detaches the child from the parent if it has one */
		void Orphan();

		/**	@brief Compare if the two scopes have the same datums with same name and same amount of data, not necessarily in the same order.
		* Checks only for structural similarity
		*	@param the scope to compare
		*	@return true if the two scopes are structurally same, false otherwise
		*/
		bool CompareStructure(const Scope& rhs) const;

		/**	@brief Return the number of datums in this scope
		*	@return the size of the scope
		*/
		std::uint32_t Size() const;
		
		/*class Iterator : public Vector<PairType*>::Iterator
		{
		public:
			bool operator==(Iterator& rhs) const;
			bool operator!=(Iterator& rhs) const;
			Iterator& operator++();
			Iterator operator++(int);
			PairType& operator*();
			Iterator& operator=(const Iterator& rhs);
		};*/

		/**	@brief Get the pair at the index from the order vector. Used for copying auxillary attributes
		*	@param position to get in the order vector
		*	@return the pair at that position
		*/
		PairType* GetPairAt(std::uint32_t index) const;
		
		/**	@brief Inserts the pair into the scope
		*	@param the pair to add to the scope
		*/
		void InsertPair(PairType* pair);
		
		Iterator begin();
		Iterator end();
		//Iterator AuxillaryBeginIterator();

	protected:
		HashMap<std::string, Datum> mTable; ///< stores the name datum pairs
		Vector<PairType*> mOrderList; ///< stores the order in which the datums were added or created

		Scope* mParent; ///< the parent of this scope or nullptr if it doesnt have one
	};
}

