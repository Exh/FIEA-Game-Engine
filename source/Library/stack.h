/**	@file stack.h
*	@brief Contains class definition of Stack
*/
#pragma once
#include "Slist.h"

namespace Library
{
	/**	@class Stack
	*	@brief Implements a templated stack
	*/
	template <typename T>
	class Stack final
	{
	public:
		/**	@brief Default constructor to initialise the stack */
		Stack();

		/**	@brief Copy constructor to deep copy two stacks 
		*	@param the stack to copy from
		*/
		Stack(const Stack& rhs);

		/**	@brief Overload of equals operator for deep copying two stacks
		*	@param the stack to copy from
		*	@return refernce to the stack copied into
		*/
		Stack& operator=(const Stack& rhs);

		/**	@brief Default destructor to clean up the stack after use */
		~Stack();

		/** @brief Add an item onto the top of the stack 
		*	@param the item to add to the stack
		*/
		void Push(const T& item);

		/**	@brief Remove an element from the top of the stack
		*	@return a copy of the top element
		*/
		T Pop();

		/**	@brief Peek or modify the element on the top of the stack without removing it.
		*	@return refernce to the element on top of the stack
		*/
		T& Top();

		/**	@brief Peek at the element on the top of the stack without removing it
		*	@return constant refernce to the element on top of the stack
		*/
		const T& Top() const;

		/**	@brief Returns the number of the elements on the stack
		*	@return number of elements in the stack
		*/
		unsigned int Size() const;

		/**	@brief Returns if the stack has any elements or not
		*	@return true, if the stack doesnt have any elements
		*/
		bool IsEmpty() const;

		/**	@brief Removes all the elements in the stack
		*/
		void Clear();

	private:
		SList<T> mSlist;
	};
}

#include "stack.inl"