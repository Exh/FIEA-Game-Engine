/**	@file Vector.inl
	@brief contains implementation for vector and its iterator
*/
#include "vector.h"

namespace Library
{
#pragma region Iterator

	template <typename T, class IncrementFunctor>
	bool Vector<T,IncrementFunctor>::Iterator::operator==(const Iterator& rhs) const
	{
		return (mOwner == rhs.mOwner && mIndex == rhs.mIndex);
	}

	template <typename T, class IncrementFunctor>
	bool Vector<T,IncrementFunctor>::Iterator::operator!=(const Iterator& rhs) const
	{
		return !(*this == rhs);
	}

	template <typename T, class IncrementFunctor>
	typename Vector<T,IncrementFunctor>::Iterator& Vector<T,IncrementFunctor>::Iterator::operator++()
	{
		if (mOwner == nullptr)
		{
			throw std::exception("Iterator's owner invalid");
		}

		if (mIndex >= mOwner->mSize)
		{
			throw std::out_of_range("Vector out of range");
		}

		++mIndex;

		return *this;
	}

	template <typename T, class IncrementFunctor>
	typename Vector<T,IncrementFunctor>::Iterator Vector<T,IncrementFunctor>::Iterator::operator++(int)
	{
		Iterator it = *this;
		operator++();
		return it;
	}

	template <typename T, class IncrementFunctor>
	T& Vector<T,IncrementFunctor>::Iterator::operator*()
	{
		if (mOwner != nullptr)
		{
			return mOwner->operator[](mIndex);
		}
		
		throw std::exception("Iterator doesnt belong to a vector");
	}

	template <typename T, class IncrementFunctor>
	typename Vector<T,IncrementFunctor>::Iterator& Vector<T,IncrementFunctor>::Iterator::operator=(const Iterator& rhs)
	{
		if (this != &rhs)
		{
			mOwner = rhs.mOwner;
			mIndex = rhs.mIndex;
		}

		return *this;
	}

	template <typename T, class IncrementFunctor>
	Vector<T,IncrementFunctor>::Iterator::Iterator(const Iterator& rhs)
		:Iterator()
	{
		*this = rhs;
	}

	template <typename T, class IncrementFunctor>
	Vector<T,IncrementFunctor>::Iterator::Iterator()
		:mOwner(nullptr), mIndex(0)
	{
	}

	template <typename T, class IncrementFunctor> 
	Vector<T, IncrementFunctor>::Iterator::Iterator(Vector* owner, std::uint32_t index)
		:mOwner(owner), mIndex(index)
	{
	}

	template <typename T, class IncrementFunctor>
	std::int32_t Vector<T, IncrementFunctor>::Iterator::operator-(const Iterator& rhs)
	{
		if (mOwner == rhs.mOwner)
		{
			return (mIndex - rhs.mIndex);
		}
		else
		{
			throw std::exception("Iterator belongs to another vector");
		}
	}
#pragma endregion

#pragma region Vector

	template <typename T, class IncrementFunctor>
	Vector<T, IncrementFunctor>::Vector(std::uint32_t capacity)
		:mSize(0), mData(nullptr), mCapacity(0)
	{
		Reserve(capacity);
	}

	template <typename T, class IncrementFunctor>
	T& Vector<T,IncrementFunctor>::operator[](const std::uint32_t& index)
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Accessing vector out of range");
		}

		return mData[index];
	}

	template <typename T, class IncrementFunctor>
	T& Vector<T,IncrementFunctor>::operator[](const std::uint32_t& index) const
	{
		if (index < 0 || index >= mSize)
		{
			throw std::out_of_range("Accessing vector out of range");
		}

		return mData[index];
	}

	template <typename T, class IncrementFunctor>
	void Vector<T,IncrementFunctor>::PopBack()
	{
		if (mSize != 0)
		{
			mSize--;
		}
		else
		{
			throw std::out_of_range("Deleting out of range");
		}
	}

	template <typename T, class IncrementFunctor>
	bool Vector<T,IncrementFunctor>::IsEmpty() const
	{
		return (mSize == 0);
	}

	template <typename T, class IncrementFunctor>
	T& Vector<T,IncrementFunctor>::Front()
	{
		return operator[](0);
	}

	template <typename T, class IncrementFunctor>
	T& Vector<T,IncrementFunctor>::Front() const
	{
		return operator[](0);
	}

	template <typename T, class IncrementFunctor>
	T& Vector<T,IncrementFunctor>::Back()
	{
		return operator[](mSize - 1);
	}

	template <typename T, class IncrementFunctor>
	T& Vector<T,IncrementFunctor>::Back() const
	{
		return operator[](mSize - 1);
	}

	template <typename T, class IncrementFunctor>
	std::uint32_t Vector<T,IncrementFunctor>::Size() const
	{
		return mSize;
	}

	template <typename T, class IncrementFunctor>
	typename Vector<T,IncrementFunctor>::Iterator Vector<T,IncrementFunctor>::begin() const
	{
		return Iterator(const_cast<Vector*>(this), 0);
	}

	template <typename T, class IncrementFunctor>
	typename Vector<T,IncrementFunctor>::Iterator Vector<T,IncrementFunctor>::end() const
	{
		return Iterator(const_cast<Vector*>(this), mSize);
	}

	template <typename T, class IncrementFunctor>
	void Vector<T,IncrementFunctor>::PushBack(const T& itemToAdd)
	{
		if (mSize + 1 > mCapacity)
		{
			std::uint32_t newCapacity = mReserveFunctor(mSize, mCapacity);
			if (newCapacity < mCapacity)
			{
				newCapacity = mCapacity + 1;
			}

			Reserve(newCapacity);
		}

		mData[mSize++] = itemToAdd;
	}

	template <typename T, class IncrementFunctor>
	Vector<T, IncrementFunctor>::Vector(const Vector& rhs)
		:Vector()
	{
		*this = rhs;
	}

	template <typename T, class IncrementFunctor>
	Vector<T, IncrementFunctor>& Vector<T, IncrementFunctor>::operator=(const Vector& rhs)
	{
		if (this != &rhs)
		{
			Clear(); //delete whats there
			Reserve(rhs.Capacity());

			for (auto& value : rhs)
			{
				PushBack(value);
			}
		}
		return *this;
	}

	template <typename T, class IncrementFunctor>
	T& Vector<T,IncrementFunctor>::At(const std::uint32_t& index)
	{
		if (index >= mCapacity)
		{
			throw std::out_of_range("Accessing vector beyond its capacity");
		}

		if (index >= mSize)
		{
			mSize = index+1;
		}

		return operator[](index);
	}

	template <typename T, class IncrementFunctor>
	Vector<T,IncrementFunctor>::~Vector()
	{
		if (mData != nullptr)
		{
			Clear();
		}
	}

	template <typename T, class IncrementFunctor>
	void Vector<T,IncrementFunctor>::Reserve(std::uint32_t newCapacity)  //paul added a fixed size to move size to capacity by calling At
	{
		if (newCapacity > mCapacity)
		{
			T* newMemory = new T[newCapacity](); 
			std::uint32_t tempSize = mSize;

			if (mSize > 0)
			{
				for (std::uint32_t i = 0; i < mSize;i++)
				{
					newMemory[i] = mData[i];
				}
			}

			Clear();
			mData = newMemory;
			mCapacity = newCapacity;
			mSize = tempSize;
		}
	}

	template <typename T, class IncrementFunctor>
	void Vector<T,IncrementFunctor>::Reserve()
	{
		std::uint32_t newCapacity = mReserveFunctor(mSize, mCapacity);
		if (newCapacity < mCapacity)
		{
			newCapacity = mCapacity + 1;
		}

		Reserve(newCapacity);
	}

	template <typename T, class IncrementFunctor>
	typename Vector<T,IncrementFunctor>::Iterator Vector<T,IncrementFunctor>::Find(const T& itemToFind)
	{
		Iterator it=begin();

		for (; it != end(); ++it)
		{
			if (*it == itemToFind)
			{
				break;
			}
		}

		return it;
	}

	template <typename T, class IncrementFunctor>
	void Vector<T,IncrementFunctor>::Clear()
	{
		delete[] mData;
		mData = nullptr;
		mSize = 0;
		mCapacity = 0;
	}

	/*
	My Remove:
	Remove(T)
		takes in the value of the item to delete, finds it in the list and deletes it, if present
	Remove(Iterator, Iterator)
		takes in 2 iterators, uses their indices and rewrites the range with the items behind the it. Both the iterators are inclusive.
	I mean, if the vector were
	1 2 3 4 5 6 x x x x
	and I wanted to delete from 3 to 5, the vector would be
	1 2 6 x x x x
	Remove(Iterator)
		takes in an iterator and deletes the element at that index.

	Tradeoffs:
	They dont actually delete the elements, just rewrite with elements behind it by deep copy.
	This could cause a lot of rewrites if the element is in the front of the list.
	With Remove(T), we need to find the element first. Finding it takes O(n)
	
	Should Remove() auto-shrink the vector?
		The users might be adding more elements immediately after Remove(), which will cause overhead to reserve and increase capacity again.
	The solution for this could be to provide another function called Shrink() if necessary, or adding a flag to Remove to indicate whether to Shrink or not.
	Since it is application based, we shouldn't make it so that Shrink happens automatically.

	What impact would Remove have on access of the Vector?
		Removing would have an impact because I am deep copying the remaining items into the ones to be deleted to fill up the gaps. 
	This depends on the number of items that follow the item(s) to delete.

	What performance implications are there?
		If the user doesn't have the Iterator to the element, it would make the remove slightly slower since we need to Find() the index of the element to delete first.
	This is being done using linear search, so it's O(n). This could be problematic in case of larger lists or if the user is trying to delete an element that is not present.
	*/
	template <typename T, class IncrementFunctor>
	void Vector<T,IncrementFunctor>::Remove(const T& itemToDelete)
	{
		Iterator it = Find(itemToDelete);

		if (it != end())
		{
			Remove(it);
		}
	}

	template <typename T, class IncrementFunctor>
	void Vector<T,IncrementFunctor>::Remove(const Iterator& firstIterator, const Iterator& lastIterator)
	{
		if (firstIterator == end() || lastIterator == end())
		{
			throw std::exception("Invalid iterator");
		}
		else if (firstIterator.mOwner != this || lastIterator.mOwner != this)
		{
			throw std::exception("Iterator doesnt belong to this vector");
		}
		else if (firstIterator.mIndex > lastIterator.mIndex)
		{
			throw std::exception("Invalid order of iterators");
		}
		else
		{
			std::uint32_t firstIndex = firstIterator.mIndex;
			std::uint32_t lastIndex = lastIterator.mIndex;

			if (firstIterator == lastIterator)
			{
				Remove(firstIterator);
			}
			else
			{
				std::uint32_t elementsLeft = mSize - lastIndex;

				if (elementsLeft != 0)
				{
					for (std::uint32_t i = 0; i<elementsLeft; i++)
					{
						mData[firstIndex + i] = mData[lastIndex + 1 + i];
					}
				}

				mSize -= (lastIndex - firstIndex+1);
			}
		}
	}

	template <typename T, class IncrementFunctor>
	void Vector<T, IncrementFunctor>::Remove(const Iterator& itemToDelete)
	{
		if (itemToDelete == end() || itemToDelete.mOwner != this)
		{
			throw std::exception("Invalid iterator");
		}
		
		std::uint32_t index = itemToDelete.mIndex;

		if (index != mSize - 1)
		{
			for (std::uint32_t i = 0; i<(mSize - index); i++)
			{
				mData[index + i] = mData[index + 1 + i];
			}
		}

		mSize--;
	}

	template <typename T, class IncrementFunctor>
	std::uint32_t Vector<T, IncrementFunctor>::Capacity() const
	{
		return mCapacity;
	}
#pragma endregion

}