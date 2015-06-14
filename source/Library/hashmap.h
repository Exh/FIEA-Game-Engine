/**	@file hashmap.h
*	@brief Definition of HashMap
*/
#pragma once

#include <utility>
//#include <cstdint> -> already included in other headers

#include "Slist.h"
#include "vector.h"
#include "DefaultHashFunctor.h"

namespace Library
{
	/**	@class HashMap
	*	@brief A templated Hashmap
	*/
	template <typename TKey, typename TData, typename DefaultHash = DefaultHashFunctor<TKey>>
	class HashMap final
	{
	public:
		typedef std::pair<TKey, TData> PairType;

	private:
		typedef SList<PairType> ChainType;
		typedef Vector<ChainType> BucketType;
		typedef typename ChainType::Iterator ChainIterator;
		typedef typename BucketType::Iterator BucketIterator;

	public:
		/**	@class Iterator
		*	@brief Inner class to assist with traversal of the hashmap
		*/
		class Iterator
		{
		public:
			friend class HashMap;

			/**	@brief Default Constructor to initialise the hashmap */
			Iterator();

			/**	@brief Copy constructor for deep copying of Iterators
			*	@param the iterator to copy from
			*/
			Iterator(const Iterator& rhs);

			/**	@brief Facilitates deep copying of iterators
			*	@param the iterator to copy from
			*	@return reference to the copy
			*/
			Iterator& operator=(const Iterator& rhs);

			/**	@brief compare this iterator with another
			*	@param the iterator to compare with
			*	@return true, if the iterators belong to the same hashmap and point to the same pair; false otherwise
			*/
			bool operator==(const Iterator& rhs) const;

			/**	@brief check if this iterator is not the same as another
			*	@param the iterator to compare with
			*	@return true, if the two iterators are not equal; false otherwise
			*/
			bool operator!=(const Iterator& rhs) const;

			/**	@brief Go to the next pair in the hashmap
			*	@return refernce to the iterator for the next data in the hashmap
			*	@throws std::out_of_range when trying to increment beyond hashmap range
			*/
			Iterator& operator++();

			/**	@brief Go to the next pair in the hashmap
			*	@return the current iterator
			*	@throws std::out_of_range when trying to increment beyond hashmap range
			*/
			Iterator operator++(int);

			/**	@brief Get the pair the iterator is pointing to
			*	@return Reference to the pair
			*	@throws std::exception if the iterator is invalid
			*/
			PairType& operator*();

			/**	@brief Get the pair the iterator is pointing to
			*	@return Address of the pair
			*	@throws std::exception if the iterator is invalid
			*/
			PairType* operator->();

		private:
			Iterator(const BucketType* owner, std::uint32_t index, const ChainIterator& iterator);
			
			const BucketType* mOwner; ///< the vector the iterator belongs to
			std::uint32_t mBucketIndex; ///< the index in the vector
			ChainIterator mChainIterator; ///< the iterator for the slist at that index
		};

		/**	@brief Explicit default constructor to reserve the hashmap capacity and initialise members*/
		explicit HashMap(std::uint32_t bucketSize=16,float loadFactor=0.75f);
		
		/**	@brief Copy constructor for deep copying of hashmaps
		*	@param the hashmap to copy from
		*/
		HashMap(const HashMap& rhs);

		/**	@brief Default destructor to clean up the hashmap */
		~HashMap();

		/**	@brief For deep copying for hashmaps
		*	@param the hashmap to copy from
		*	@return reference to the copied hashmap
		*/
		HashMap& operator=(const HashMap& rhs);
		
		/**	@brief Insert a pair into the hashmap. Value is not modified if the key is already present
		*	@param refernce to the pair
		*	@return iterator to the inserted pair
		*/
		Iterator Insert(const PairType& pair);

		/**	@brief Insert a pair into the hashmap. Value is not modified if the key is already present
		*	@param refernce to the pair
		*	@param returns true if the pair was inserted, false otherwise
		*	@return iterator to the inserted pair
		*/
		Iterator Insert(const PairType& pair, bool& valueInserted);

		/**	@brief Insert a key with the corresponding value into the hashmap. Value is not modified if the key is already present
		*	@param refernce to the key
		*	@param reference to the value
		*	@return iterator to the inserted pair
		*/
		Iterator Insert(const TKey& key, const TData& data);

		/**	@brief Insert a key with the corresponding value into the hashmap. Value is not modified if the key is already present
		*	@param refernce to the pair
		*	@param returns true if the values were inserted, false otherwise
		*	@return iterator to the inserted pair
		*/
		Iterator Insert(const TKey& key, const TData& data, bool& valueInserted);

		/**	@brief Return the value for the specified key. Key is inserted if it is not present in the table
		*	@param reference to the key
		*	@return reference to the value associated with the key, if it is present; or reference to dummy data, otherwise
		*/
		TData& operator[](const TKey& key);

		/**	@brief Return the value for the specified key. Key is NOT inserted if it is not present in the table
		*	@param reference to the key
		*	@return reference to the value associated with the key, if it is present
		*	@throws std::out_of_range, if the key is not present
		*/
		TData& At(const TKey& key) const;

		/**	@brief removes the key and value from the hashmap
		*	@param the key of the pair to remove
		*/
		void Remove(const TKey& key);

		/**	@brief erases all the contents of the hashmap retaining its capacity */
		void Clear();

		/**	@brief Accessor for the number of elements in the hashmap
		*	@return number of elements added
		*/
		std::uint32_t Size() const;

		/**	@brief Accessor for the capacity of the hashmap
		*	@return the number of buckets in the hashmap
		*/
		std::uint32_t BucketSize() const;

		/**	@brief Locates the pair in the hashmap using the key
		*	@param the key for the required pair
		*	@return iterator to the pair if present; end() otherwise
		*/
		Iterator Find(const TKey& key) const;

		/**	@brief Checks if the specified key is present in the hashmap
		*	@param the key
		*	@return true, if the key is present; false, otherwise
		*/
		bool ContainsKey(const TKey& key) const;

		/**	@brief denotes the beginning of the hashmap
		*	@return the iterator to the first element in the hashmap
		*/
		Iterator begin() const;

		/**	@brief denotes one past the end of the hashmap
		*	@return the iterator to one past the end of the hashmap
		*/
		Iterator end() const;

		/**	@brief Mutator for the maximum desired load factor for the hashmap
		*	@param the maximum load factor
		*/
		void SetMaxLoadFactor(float loadFactor);

		/**	@brief Accessor for the maximum desired load factor for the hashmap
		*	@return the maximum load factor
		*/
		float GetMaxLoadFactor() const;

		/**	@brief Accessor for the load factor of the hashmap. Calculated as (number of elements in the hashmap / total number of buckets)
		*	@return the load factor
		*/
		float GetLoadFactor() const;

		/**	@brief Rehash the table with the new size. If the size is less than or equal to current size, the hashmap is doubled in size
		*	@param new capacity of the hashmap
		*/
		void RehashTable(std::uint32_t newTableSize=0);

		/** @brief Get if the hashmap should be resized automatically when the load factor is reached
		*	@return the value of auto rehash
		*/
		bool AutoRehash() const;

		/** @brief Set if the hashmap should be resized automatically when the load factor is reached
		*	@param the new value of auto rehash
		*/
		void SetAutoRehash(bool autoRehash);

		void Reserve(std::uint32_t bucketSize=16);

	private:
		BucketType mHashTable; ///< the vector
		DefaultHash mHash; ///< the hash functor

		std::uint32_t mElementsCount; ///< number of elements in the hashmap
		float mMaxLoadFactor; ///< maximum load factor
		bool mAutoRehash; ///< if the hashmap should automatically resize if the max load factor is reached
	};
}
#include "hashmap.inl"