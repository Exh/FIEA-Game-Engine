/**	@file Slist.h
*	@brief Contains declaration of templated class SList
*/
#pragma once

#include <cstdint>
#include <exception>
#include <stdexcept>

namespace Library
{
	/**	@class SList
	*	@brief A templated Singly Linked List class
	*/
	template <typename T>
	class SList final
	{
	private:
		/**	@class Node
		*	@brief Helper class that defines each node in the singly linked list
		*/
		class Node
		{
		public:
			T mData;		///< Data that the node holds
			Node* mNext;	///< Pointer to the next node, or nullptr if it's the last node in the list

			/**	@brief Overloaded constructor to initialise the node with the required data and next pointer
			*	@param data : reference to the data the node should hold
			*	@param next : pointer to the next node in the list, default value is nullptr
			*/
			Node(const T& data, Node* next = nullptr);

		private:
			/** @brief Default constructor disabled for security */
			Node(const Node& rhs) = delete;

			/** @brief Copying the node disabled for security */
			Node& operator=(const Node& rhs) = delete;
		};

	public:
		/**	@class Iterator 
		*	@brief Iterator to help traverse the SList
		*/
		class Iterator
		{
		public:
			friend class SList; ///< To allow Slist to access Iterator's private members

			/** @brief Deafult constructor to set its members to empty */
			Iterator();

			/** @brief Copy constructor to create shallow copy of rhs */
			Iterator(const Iterator& rhs);

			/** @brief To create a shallow copy of rhs
			*	@param The Iterator to copy from
			*	@return Refernce to the copied iterator 
			*/
			Iterator& operator=(const Iterator& rhs);

			/** @brief Comparison of this iterator with another 
			*	@param the iterator to compare to
			*	@return true, if the two iterators point to the same item in the list 
			*/
			bool operator==(const Iterator& rhs) const;

			/** @brief Negative comparison of two iterators
			*	@param the iterator to compare with
			*	@return true, if the two iterators don't point to the same item in the list
			*/
			bool operator!=(const Iterator& rhs) const;

			/** @brief Moves the iterator to the item in the list 
			*	@return reference to the iterator for the next item
			*/
			Iterator& operator++();

			/** @brief Moves the iterator to the item in the list
			*	@return the iterator of the current item
			*/
			Iterator operator++(int);

			/** @brief Get the value the iterator is pointing at
			*	@return reference to the value
			*/
			T& operator*();
		private:
			/** @brief Overloaded constructor to set owner and node for the iterator
			*	Will be used to create iterator during begin and end method calls
			*/
			Iterator(const SList* owner, Node* node);

			const SList* mOwner; ///< the list the iterator belongs to
			Node* mNode; ///< the node the iterator is pointing to
		};

		/**	@brief Default constructor that initialises members to default values */
		SList();

		/**	@brief Copy constructor to for deep copying of one singly linked list into another. 
		*	The list passed in will not be modified
		*	@param reference to the list whose contents to copy
		*/
		SList(const SList& rhs);

		/**	@brief Overloading for = to allow deep copying of one singly linked list into another.
		*	The list passed in will not be modified
		*	@param reference to the list whose contents to copy
		*/
		SList& operator=(const SList& rhs);

		/** @brief Method to add an element to the beginning of the list
		*	@param reference to the data to be inserted into the list
		*/
		void PushFront(const T& data);

		/**	@brief Method to append an element to the end of the list
		*	@param reference to the data to be appended to the list
		*/
		Iterator PushBack(const T& data);

		/** @brief Method to remove the first element of the list
		*	Note: The element will not be returned. Use Front() to obtain the first element
		*	@throw throws a std::exception when attempted to pop from an empty list
		*/
		void PopFront();

		/** @brief Method to return data from the beginning of the list
		*	@return the first element in the list
		*	@throw throws a std::exception if Front() is called on an empty list
		*/
		T& Front();

		/**	@brief Method to return data from the end of the list
		*	@return the last element in the list
		*	@throw throws a std::exception if Back() is called on an empty list
		*/
		T& Back();

		/**	@brief Destructor to clear off the list during delete */
		~SList();

		/** @brief Method to clear the contents of the list */
		void Clear();

		/** @brief Method to return the size of the list
		*	@return length of the list
		*/
		std::uint32_t Size() const;

		/**	@brief Method to return if the list has contents in it
		*	@return true if the list contains elements 
		*/
		bool IsEmpty() const;

		/** @brief Denotes the beginning of the list
		*	@return the iterator for the beginning of the list
		*/
		Iterator begin() const;

		/** @brief Denotes one past the end of the list
		*	@return the iterator for the end of the list
		*/
		Iterator end() const;

		/** @brief Insert the specified value anywhere in the list after the item the iterator is pointing to
		*	@param the iterator to the required item after which to add
		*	@param the value of the item to be inserted
		*/
		void InsertAfter(const Iterator& it, const T& value);

		/** @brief Find the item with the specified value
		*	@param the value to find
		*	@return the iterator pointing to the found item, or end of list if no such item was found
		*/
		Iterator Find(const T& value) const;

		/** @brief Removes the item with the specified value. The item will be removed only if present in the list.
		*	It does not provide any indication if no such value is found, just leaves the list unaltered
		*	@param the value to remove from the list.
		*/
		void Remove(const T& value);

	/*	bool operator==(const SList& rhs) const;
		bool operator!=(const SList& rhs) const;*/

	private:
		Node* mFront; //Pointer to the first element in the list
		Node* mBack; //Pointer to the last element in the list
		std::uint32_t mSize; //holds the number of nodes in the list
	};
}

#include "Slist.inl"