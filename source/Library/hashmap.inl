/**	@file hashmap.inl
*	@brief implementation of HashMap
*/
#include "hashmap.h"

namespace Library
{
#pragma region HashMap

	template <typename TKey, typename TData, typename DefaultHash>
	HashMap<TKey, TData, DefaultHash>::HashMap(std::uint32_t bucketSize, float loadFactor)
		:mMaxLoadFactor(loadFactor), mElementsCount(0), mAutoRehash(false)
	{
		mHashTable.Reserve(bucketSize);
		mHashTable.At(bucketSize - 1); //make the entire vector accessible at once
	}

	template <typename TKey, typename TData, typename DefaultHash>
	HashMap<TKey, TData, DefaultHash>::HashMap(const HashMap& rhs)
		:mHashTable(rhs.mHashTable), mHash(rhs.mHash), mElementsCount(rhs.mElementsCount), mMaxLoadFactor(rhs.mMaxLoadFactor), mAutoRehash(rhs.mAutoRehash)
	{
	}

	template <typename TKey, typename TData, typename DefaultHash>
	HashMap<TKey, TData, DefaultHash>::~HashMap()
	{
		//Clear is done by vector
		//if (mElementsCount!=0)
		//{
		//	Clear();
		//}
	}

	template <typename TKey, typename TData, typename DefaultHash>
	HashMap<TKey, TData, DefaultHash>& HashMap<TKey, TData, DefaultHash>::operator=(const HashMap& rhs)
	{
		if (this != &rhs)
		{
			mHashTable = rhs.mHashTable;
			mElementsCount = rhs.mElementsCount;
			mMaxLoadFactor = rhs.mMaxLoadFactor;
			mAutoRehash = rhs.mAutoRehash;
			mHash = rhs.mHash;
		}

		return *this;
	}

	template <typename TKey, typename TData, typename DefaultHash>
	typename HashMap<TKey, TData, DefaultHash>::Iterator HashMap<TKey, TData, DefaultHash>::Insert(const PairType& pair)
	{
		Iterator it = Find(pair.first); //find the key
		
		//insert the pair if the key is not found
		if (it==end())
		{
			++mElementsCount;

			//resize the table if required
			if (mAutoRehash && GetLoadFactor() > mMaxLoadFactor)
			{
				RehashTable(mHashTable.Size() * 2);
			}

			//get index by hashing key and modding with size
			std::uint32_t index = mHash(pair.first) % mHashTable.Size();

			//push the pair onto the list
			auto listIt = mHashTable[index].PushBack(pair);

			//it = Find(pair.first); //get iterator to it
			it = Iterator(&mHashTable, index, listIt);
		}

		return it;
	}

	template <typename TKey, typename TData, typename DefaultHash>
	typename HashMap<TKey, TData, DefaultHash>::Iterator HashMap<TKey, TData, DefaultHash>::Insert(const TKey& key, const TData& data)
	{
		return Insert(std::pair<TKey,TData>(key, data));
	}

	template <typename TKey, typename TData, typename DefaultHash>
	typename HashMap<TKey, TData, DefaultHash>::Iterator HashMap<TKey, TData, DefaultHash>::Insert(const PairType& pair, bool& valueInserted)
	{
		Iterator it = Find(pair.first); //find the key

		//insert the pair if the key is not found
		if (it == end())
		{
			++mElementsCount;

			//resize the table if required
			if (mAutoRehash && GetLoadFactor() > mMaxLoadFactor)
			{
				RehashTable(mHashTable.Size() * 2);
			}

			//get index by hashing key and modding with size
			std::uint32_t index = mHash(pair.first) % mHashTable.Size();

			//push the pair onto the list
			auto listIt =mHashTable[index].PushBack(pair);
			valueInserted = true;
			//it = Find(pair.first); //get iterator to it
			it = Iterator(&mHashTable, index, listIt);
				//Iterator(this, index, const_cast<const ChainIterator&>(listIt));
		}
		else
		{
			valueInserted = false;
		}

		return it;
	}

	template <typename TKey, typename TData, typename DefaultHash>
	typename HashMap<TKey, TData, DefaultHash>::Iterator HashMap<TKey, TData, DefaultHash>::Insert(const TKey& key, const TData& data, bool& valueInserted)
	{
		return Insert(std::pair<TKey, TData>(key, data), valueInserted);
	}


	template <typename TKey, typename TData, typename DefaultHash>
	TData& HashMap<TKey, TData, DefaultHash>::operator[](const TKey& key)
	{
		//Iterator it = Find(key); //find the key

		////insert if not present
		//if (it == end())
		//{
		//	Insert(PairType(key, TData())); //insert key with a dummy value
		//	
		//	it = Find(key); //get iterator to it
		//}

		Iterator it = Insert(PairType(key, TData()));
		return (*it).second;
	}

	template <typename TKey, typename TData, typename DefaultHash>
	TData& HashMap<TKey, TData, DefaultHash>::At(const TKey& key) const
	{
		if (!ContainsKey(key))
		{
			throw std::out_of_range("Key not found");
		}

		return Find(key)->second;
	}

	template <typename TKey, typename TData, typename DefaultHash>
	void HashMap<TKey, TData, DefaultHash>::Remove(const TKey& key)
	{
		Iterator it = Find(key); //find key

		//remove if present
		if (it != end())
		{
			mHashTable[it.mBucketIndex].Remove(*it);
			--mElementsCount;
		}
	}

	template <typename TKey, typename TData, typename DefaultHash>
	void HashMap<TKey, TData, DefaultHash>::Clear()
	{
		for (auto& bucket : mHashTable)
		{
			bucket.Clear();
		}

		mElementsCount = 0;
	}

	template <typename TKey, typename TData, typename DefaultHash>
	std::uint32_t HashMap<TKey, TData, DefaultHash>::Size() const
	{
		return mElementsCount;
	}

	template <typename TKey, typename TData, typename DefaultHash>
	typename HashMap<TKey, TData, DefaultHash>::Iterator HashMap<TKey, TData, DefaultHash>::Find(const TKey& key) const
	{	
		Iterator it;

		//find index of the key
		std::uint32_t index = mHash(key) % mHashTable.Size();

		//create iterators to the slist
		ChainIterator pairIt = mHashTable[index].begin();
		ChainIterator pairEnd = mHashTable[index].end();

		bool foundKey = false;

		for (; pairIt != pairEnd; ++pairIt)
		{
			if ((*pairIt).first == key)
			{
				foundKey = true;
				break;
			}
		}

		if (foundKey)
		{
			it = Iterator(&mHashTable,index,pairIt); //create a hashmap iterator
		}
		else
		{
			it = end();
		}

		return it;
	}
	
	template <typename TKey, typename TData, typename DefaultHash>
	bool HashMap<TKey, TData, DefaultHash>::ContainsKey(const TKey& key) const
	{
		return (Find(key) != end());
	}

	template <typename TKey, typename TData, typename DefaultHash>
	typename HashMap<TKey, TData, DefaultHash>::Iterator HashMap<TKey, TData, DefaultHash>::begin() const
	{
		std::uint32_t index = 0;
		while (index < mHashTable.Size() && mHashTable[index].Size() == 0)
		{
			++index;
		}
		
		if (index >= mHashTable.Size()) //return end if the iterator is empty
		{
			return end();
		}

		return Iterator(&mHashTable, index, mHashTable[index].begin());
	}

	template <typename TKey, typename TData, typename DefaultHash>
	typename HashMap<TKey, TData, DefaultHash>::Iterator HashMap<TKey, TData, DefaultHash>::end() const
	{
		return Iterator(&mHashTable, mHashTable.Size(), ChainIterator());
	}

	template <typename TKey, typename TData, typename DefaultHash>
	void HashMap<TKey, TData, DefaultHash>::RehashTable(std::uint32_t newTableSize)
	{
		if (newTableSize <= mHashTable.Size())
		{
			newTableSize = mHashTable.Size() * 2;
		}

		HashMap<TKey, TData, DefaultHash> newHashTable(newTableSize); //create a new hash map

		Iterator it = begin();

		//walk through the old hashmap and insert into the new hashmap
		for (; it != end();++it)
		{
			newHashTable.Insert(*it);
		}
		
		Clear();
		*this = newHashTable; //copy new hashmap into old one

		newHashTable.Clear(); //clean up the new one
	}

	template <typename TKey, typename TData, typename DefaultHash>
	void HashMap<TKey, TData, DefaultHash>::SetMaxLoadFactor(float loadFactor)
	{
		mMaxLoadFactor = loadFactor;
	}

	template <typename TKey, typename TData, typename DefaultHash>
	float HashMap<TKey, TData, DefaultHash>::GetMaxLoadFactor() const
	{
		return mMaxLoadFactor;
	}

	template <typename TKey, typename TData, typename DefaultHash>
	float HashMap<TKey, TData, DefaultHash>::GetLoadFactor() const 
	{
		return ((float)mElementsCount/(float)mHashTable.Size());
	}

	template <typename TKey, typename TData, typename DefaultHash>
	std::uint32_t HashMap<TKey, TData, DefaultHash>::BucketSize() const
	{
		return mHashTable.Size();
	}
#pragma endregion

#pragma region Iterator
	template <typename TKey, typename TData, typename DefaultHash>
	HashMap<TKey, TData, DefaultHash>::Iterator::Iterator()
		: mBucketIndex(0), mOwner(nullptr)
	{
	}
	
	template <typename TKey, typename TData, typename DefaultHash>
	HashMap<TKey, TData, DefaultHash>::Iterator::Iterator(const Iterator& rhs)
		: Iterator(rhs.mOwner,rhs.mBucketIndex,rhs.mChainIterator)
	{
	}

	template <typename TKey, typename TData, typename DefaultHash>
	HashMap<TKey, TData, DefaultHash>::Iterator::Iterator(const BucketType* owner, std::uint32_t index, const ChainIterator& iterator)
		: mBucketIndex(index), mChainIterator(iterator), mOwner(owner)
	{
	}

	template <typename TKey, typename TData, typename DefaultHash>
	typename HashMap<TKey, TData, DefaultHash>::Iterator& HashMap<TKey, TData, DefaultHash>::Iterator::operator=(const Iterator& rhs)
	{
		if (this != &rhs)
		{
			mOwner = rhs.mOwner;
			mBucketIndex = rhs.mBucketIndex;
			mChainIterator = rhs.mChainIterator;
		}

		return *this;
	}

	template <typename TKey, typename TData, typename DefaultHash>
	bool HashMap<TKey, TData, DefaultHash>::Iterator::operator==(const Iterator& rhs) const
	{
		return (mOwner == rhs.mOwner && mBucketIndex == rhs.mBucketIndex && mChainIterator == rhs.mChainIterator);
	}

	template <typename TKey, typename TData, typename DefaultHash>
	bool HashMap<TKey, TData, DefaultHash>::Iterator::operator!=(const Iterator& rhs) const
	{
		return !(*this == rhs);
	}

	template <typename TKey, typename TData, typename DefaultHash>
	typename HashMap<TKey, TData, DefaultHash>::Iterator& HashMap<TKey, TData, DefaultHash>::Iterator::operator++()
	{
		if (mOwner == nullptr || mBucketIndex >= mOwner->Size())
		{
			throw std::out_of_range("Accessing out of range");
		}

		++mChainIterator;

		if (mChainIterator == mOwner->operator[](mBucketIndex).end()) //if iterator has reached end, go to the next valid one
		{
			do
			{
				++mBucketIndex;

			} while (mBucketIndex < mOwner->Size() && mOwner->operator[](mBucketIndex).Size() == 0); //continue if next item is empty or if end of hashmap is reached
			
			if (mBucketIndex >= mOwner->Size())
			{
				*this = Iterator(mOwner, mOwner->Size(), ChainIterator());
			}
			else
			{
				mChainIterator = mOwner->operator[](mBucketIndex).begin();
			}
		}

		return *this;
	}

	template <typename TKey, typename TData, typename DefaultHash>
	typename HashMap<TKey, TData, DefaultHash>::Iterator HashMap<TKey, TData, DefaultHash>::Iterator::operator++(int)
	{
		Iterator it = *this;
		operator++();
		return it;
	}
	
	template <typename TKey, typename TData, typename DefaultHash>
	typename HashMap<TKey, TData, DefaultHash>::PairType& HashMap<TKey, TData, DefaultHash>::Iterator::operator*()
	{
		if (mOwner == nullptr || mBucketIndex >= mOwner->Size())
		{
			throw std::exception("Invalid iterator");
		}

		return *mChainIterator;
	}

	template <typename TKey, typename TData, typename DefaultHash>
	typename HashMap<TKey, TData, DefaultHash>::PairType* HashMap<TKey, TData, DefaultHash>::Iterator::operator->()
	{
		if (mOwner == nullptr || mBucketIndex >= mOwner->Size())
		{
			throw std::exception("Invalid iterator");
		}

		return &(*mChainIterator);
	}
#pragma endregion
	template <typename TKey, typename TData, typename DefaultHash>
	bool HashMap<TKey, TData, DefaultHash>::AutoRehash() const
	{
		return mAutoRehash;
	}

	template <typename TKey, typename TData, typename DefaultHash>
	void HashMap<TKey, TData, DefaultHash>::SetAutoRehash(bool autoRehash)
	{
		mAutoRehash = autoRehash;
	}

	template <typename TKey, typename TData, typename DefaultHash>
	void HashMap<TKey, TData, DefaultHash>::Reserve(std::uint32_t bucketSize = 16)
	{
		mHashTable.Reserve(bucketSize);
	}
}