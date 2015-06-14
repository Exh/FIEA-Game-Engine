/**	@file Slist.inl
*	@brief Inline header implementation for SList templated class
*/
#include "Slist.h"

namespace Library
{
#pragma region Node
	template <typename T>
	SList<T>::Node::Node(const T& data, Node* next):
		mData(data), mNext(next)
	{
	}
#pragma endregion

#pragma region SList
	template <typename T>
	bool SList<T>::IsEmpty() const
	{
		return mSize == 0;
	}

	template <typename T>
	std::uint32_t SList<T>::Size() const
	{
		return mSize;
	}

	template <typename T>
	SList<T>::SList():
		mSize(0), mFront(nullptr), mBack(nullptr)
	{
	}

	template <typename T>
	SList<T>::~SList()
	{
		Clear();
	}

	template <typename T>
	SList<T>::SList(const SList& rhs) :SList()
	{
		*this = rhs;
	}

	template <typename T>
	SList<T>& SList<T>::operator=(const SList<T>& rhs)
	{
		if (this != &rhs) //when comparing to itself, dont copy
		{
			Clear();
		
			//for (auto it = rhs.begin(); it != rhs.end(); ++it)
			for (auto& value : rhs)
			{
				PushBack(value);
			}
		}
		return *this;
	}

	template <typename T>
	void SList<T>::PushFront(const T& data)
	{
		Node* newNode = new Node(data, mFront);
		mFront = newNode;

		if (IsEmpty())
		{
			mBack = newNode;
		}
		++mSize;	
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::PushBack(const T& data)
	{
		Node* newNode = new Node(data);
		
		if (mBack != nullptr)
		{
			mBack->mNext = newNode;
		}
		mBack = newNode;
		
		if (IsEmpty())
		{
			mFront = newNode;
		}
		++mSize;

		return Iterator(this, newNode);
	}

	template <typename T>
	void SList<T>::PopFront()
	{
		if (!IsEmpty())
		{
			Node* newFrontNode = mFront->mNext;

			delete(mFront);
			mFront = newFrontNode;

			mSize--;
			if (IsEmpty())
			{
				mBack = nullptr;
			}
		}
		else
		{
			throw std::exception("List is empty");
		}
	}

	template <typename T>
	T& SList<T>::Front()
	{
		if (IsEmpty())
		{
			throw std::exception("List is empty");
		}
		
		return mFront->mData;
	}

	template <typename T>
	T& SList<T>::Back()
	{
		if (IsEmpty())
		{
			throw std::exception("List is empty");
		}

		return mBack->mData;
	}

	template <typename T>
	void SList<T>::Clear()
	{
		while (mFront != nullptr) //or mSize>0
		{
			PopFront();
		}
	}

	template <typename T>
	void SList<T>::InsertAfter(const Iterator& it, const T& value)
	{
		if (this == it.mOwner)
		{
			if (it == end()) //|| mBack == it.mNode, paul did it here
			{
				PushBack(value);
			}
			else
			{
				Node* newNode = new Node(value, it.mNode->mNext);

				if (mBack == it.mNode)
				{
					mBack = newNode;
				}
				it.mNode->mNext = newNode;
				++mSize;
			}
		}
		else
		{
			throw std::exception("Iterator belongs to another list");
		}
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::Find(const T& value) const
	{
		Iterator it = begin();
		for (; it != end(); ++it) // auto it = begin() -> what i did
		{
			if (*(it) == value)
			{
				//return it; -> multiple return
				break;
			}
		}

		//return end();
		return it;
	}

	template <typename T>
	void SList<T>::Remove(const T& value)
	{
		bool nodeFound = false;
		Iterator it = begin();
		Node* prevNode = nullptr;

		while (it != end())
		{
			if (*(it) == value)
			{
				nodeFound = true;
				break;
			}
			prevNode = it.mNode;
			++it;
		}

		if (nodeFound)
		{
			Node* nextNode = it.mNode->mNext;

			if (it.mNode == mFront)
			{
				mFront = nextNode;
			}
			else
			{
				prevNode->mNext = nextNode;
			}

			if (it.mNode == mBack)
			{
				mBack = prevNode;
			}

			delete(it.mNode);
			it.mNode = nextNode;
			--mSize;
		}
	}

	//template <typename T>
	//bool SList<T>::operator==(const SList& rhs) const
	//{
	//	if (rhs != nullptr && this==&rhs)
	//	{
	//		return true;
	//	}

	//	return false;
	//}

	//template <typename T>
	//bool SList<T>::operator!=(const SList& rhs) const
	//{
	//	return !(*this == rhs);
	//}
#pragma endregion

#pragma region Iterator
	template <typename T>
	SList<T>::Iterator::Iterator()
		:mOwner(nullptr), mNode(nullptr)
	{
	}

	template <typename T>
	SList<T>::Iterator::Iterator(const Iterator& rhs) : Iterator()
	{
		*this = rhs;
	}

	template <typename T>
	typename SList<T>::Iterator& SList<T>::Iterator::operator=(const Iterator& rhs)
	{
		if (this != &rhs)
		{
			mOwner = rhs.mOwner;
			mNode = rhs.mNode;
		}
		return *this;
	}

	template <typename T>
	bool SList<T>::Iterator::operator==(const Iterator& rhs) const
	{
		return (mOwner == rhs.mOwner && mNode == rhs.mNode);
	}

	template <typename T>
	bool SList<T>::Iterator::operator!=(const Iterator& rhs) const
	{
		return !(*this==rhs);
	}

	template <typename T>
	typename SList<T>::Iterator& SList<T>::Iterator::operator++()
	{
		if (mNode != nullptr)
		{
			mNode = mNode->mNext;
		}

		//throw std::out_of_range("Iterator is not pointing to anything");
		return *this;
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::Iterator::operator++(int)
	{
		Iterator it = *this;
		operator++(); // or ++(*this);
		return it;
	}

	template <typename T>
	T& SList<T>::Iterator::operator*()
	{
		if (mNode != nullptr)
		{
			return mNode->mData;
		}

		throw std::out_of_range("Iterator is not pointing to anything");
	}

	template <typename T>
	SList<T>::Iterator::Iterator(const SList* owner, Node* node)
		:mOwner(owner), mNode(node)
	{
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::begin() const
	{
		return Iterator(this, mFront);
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::end() const
	{
		return Iterator(this, nullptr);
	}
#pragma endregion
}