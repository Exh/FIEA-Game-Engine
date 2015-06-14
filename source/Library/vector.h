/**	@file vector.h
*	@brief definition for Vector class
*/
#pragma once

#include <cstdint>
#include <stdexcept>
#include <exception>
#include "DefaultVectorFunctor.h"

namespace Library
{
	template <typename T,class IncrementFunctor = DefaultVectorFunctor>
	/**	@class Vector
	*	@brief Templated dynamic array
	*/
	class Vector final
	{
	public:
		/**	@class Iterator
		*	@brief Iterator for Vector
		*/
		class Iterator
		{
		public :
			friend class Vector;

			/**	@brief Equality check for iterators
			*	@param the iterator to compare to
			*	@return true if the two iterators belong to the same vector and point to the same data
			*/
			bool operator==(const Iterator& rhs) const;

			/**	@brief Inequality check for iterators
			*	@param the iterator to compare to
			*	@return true, if the two iterators don't belong to the same vector or point to the same data
			*/
			bool operator!=(const Iterator& rhs) const;

			/**	@brief Advance iterator to the next item
			*	@return Iterator for the adjacent element
			*/
			Iterator& operator++();

			/**	@brief Advance iterator to the next item
			*	@return Iterator for the same element
			*/
			Iterator operator++(int);

			/**	@brief Get the item the iterator points to
			*	@return Value of the element
			*/
			T& operator*();

			/**	@brief Deep copy of iterators
			*	@param The iterator to copy from
			*	@return reference to the new iterator
			*/
			Iterator& operator=(const Iterator& rhs);

			/**	@brief Deep copy of iterators
			*	@param the iterator to copy from
			*/
			Iterator(const Iterator& rhs);

			/**	@brief default constructor to set value to default */
			Iterator();

			/**	@brief find the number of elements between two iterators. 
			* It blindly calculates without regard for where the iterator is.
			* Note : value may be negative if order of iterators is reversed
			*	@param the iterator to compare to
			*	@return the number of elements between the two iterators
			*	@throw std::exception is iterator belongs to another vector
			*/
			std::int32_t operator-(const Iterator& rhs);
		private:
			Iterator(Vector* owner, std::uint32_t index);
			Vector* mOwner;
			std::uint32_t mIndex;
		};

		/**	@brief Overloaded constructor that serves as default constructor if no value is passed in.
		*	@param the required initial capacity for the vector
		*/
		explicit Vector(std::uint32_t capacity=0); //explicit so that we dont say vector<foo> v=1 and they have to say vector<foo> v(1)
		
		/**	@brief Default destructor to clear the list and ensure no memory leak */
		~Vector();

		/**	@brief delete the elements in the vector and reset its capacity
		*/
		void Clear();

		/**	@brief access the item at the given index
		*	@param the index to access
		*	@return reference to the value at the given index
		*	@throw std::out_of_range when trying to access above or below valid range
		*/
		T& operator[](const std::uint32_t& index);
		
		/**	@brief access the item at the given index
		*	@param the index to access
		*	@return constant reference to the value at the given index
		*	@throw std::out_of_range when trying to access above or below valid range
		*/
		T& operator[](const std::uint32_t& index) const;
		
		/**	@brief access the item at the given index.
		* Can also access beyond the size of the vector. Use this at your own discretion.
		*	@param the index to access
		*	@return reference to the value at that index
		*	@throw std::out_of_range when trying to access beyond the capacity of the vector
		*/
		T& At(const std::uint32_t& index);

		/**	@brief adds an element to the end of the vector.
		* It automatically increases the capacity of the vector if necessary to accomodate the new element
		*	@param the item to add to the vector
		*/
		void PushBack(const T& itemToAdd);

		/**	@brief Remove the last element in the vector
		*	@throw std::out_of_range when trying to delete below valid range
		*/
		void PopBack();

		/**	@brief Returns if the vector contains elements
		*	@return true if vector has no elements
		*/
		bool IsEmpty() const;

		/**	@brief Returns the number of elements in the vector
		*	@return count of the elements
		*/
		std::uint32_t Size() const;

		/**	@brief access to first element in the vector
		*	@return reference to the first element
		*	@throw std::out_of_range if the vector is empty
		*/
		T& Front();

		/**	@brief access to first element in the vector
		*	@return constant reference to the first element
		*	@throw std::out_of_range if the vector is empty
		*/
		T& Front() const;

		/**	@brief access to last element in the vector
		*	@return reference to the last element
		*	@throw std::out_of_range if the vector is empty
		*/
		T& Back();

		/**	@brief access to last element in the vector
		*	@return constant reference to the last element
		*	@throw std::out_of_range if the vector is empty
		*/
		T& Back() const;
		
		/**	@brief denotes the front of the vector
		*	@return iterator to the front of the vector
		*/
		Iterator begin() const;
		
		/**	@brief denoted one past the last element in the vector
		*	@return iterator to one past the vector
		*/
		Iterator end() const;
		
		/**	@brief Deep copy of vectors
		*	@param the vector to copy from
		*/
		Vector(const Vector& rhs);
		
		/**	@brief Deep copy of vectors
		*	@param the vector to copy from
		*	@return reference to the new vector
		*/
		Vector& operator=(const Vector& rhs);
	
		/**	@brief increases the capacity of the vector.
		* Note : you cannot shrink the vector
		*	@param the new capacity of the vector
		*/
		void Reserve(std::uint32_t newCapacity);
		
		/**	@brief reserve with the specified reserve scheme. 
		* The default scheme will be used to double the capacity each time necessary, in case one is not provided.
		*/
		void Reserve();
	
		/**	@brief to locate an element in the vector
		*	@param the value of the element to find
		*	@return iterator to the element or end() if not found
		*/
		Iterator Find(const T& itemToFind);
		
		/**	@brief removes an element from the vector
		*	@param the item to remove from vector
		*/
		void Remove(const T& itemToDelete);
		
		/**	@brief to remove a range of elements from the vector
		*	@param starting element in the range
		*	@param the last element in the range
		*	@throw std::exception when either of the iterators are invalid, belong to another
		* or if the order of the iterators are reversed
		*/
		void Remove(const Iterator& firstIterator, const Iterator& lastIterator);
		
		/**	@brief remove an element using its iterator
		*	@param the iterator to the item to delete
		*	@throw std::exception id the iterator is invalid
		*/
		void Remove(const Iterator& itemToDelete);
		
		/**	@brief returns the capacity of vector. 
		* Capacity denotes the maximum number of elements the vector can currently hold
		*	@return the capacity
		*/
		std::uint32_t Capacity() const;

	private:
		T* mData;
		std::uint32_t mSize;
		std::uint32_t mCapacity;
		IncrementFunctor mReserveFunctor;
	};
}

#include "vector.inl"
