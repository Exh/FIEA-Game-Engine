/** @file stack.inl
*	@brief Implementation of stack class
*/
#include "stack.h"

namespace Library
{
	template <typename T>
	Stack<T>::Stack()
		:mSlist()
	{
	}

	template <typename T>
	Stack<T>::Stack(const Stack& rhs)
		: mSlist(rhs.mSlist)
	{
		//*this = rhs; -> dont do this
	}

	template <typename T>
	Stack<T>& Stack<T>::operator=(const Stack& rhs)
	{
		if (this != &rhs)
		{
			mSlist = rhs.mSlist;
		}
		return *this;
	}
	
	template <typename T>
	Stack<T>::~Stack()
	{
		if (!mSlist.IsEmpty())
		{
			Clear();
		}
	}

	template <typename T>
	void Stack<T>::Push(const T& item)
	{
		mSlist.PushFront(item);
	}

	template <typename T>
	T Stack<T>::Pop()
	{
		T temp = mSlist.Front();
		mSlist.PopFront();
		return temp;
	}

	template <typename T>
	T& Stack<T>::Top()
	{
		return mSlist.Front();
	}

	template <typename T>
	const T& Stack<T>::Top() const
	{
		return mSlist.Front();
	}

	template <typename T>
	unsigned int Stack<T>::Size() const
	{
		return mSlist.Size();
	}

	template <typename T>
	bool Stack<T>::IsEmpty() const
	{
		return mSlist.IsEmpty();
	}

	template <typename T>
	void Stack<T>::Clear()
	{
		if (!mSlist.IsEmpty())
		{
			mSlist.Clear();
		}
	}
}