/**	@file DefaultHashFunctor.h
*	@brief Contains defintion of class DefaultHashFunctor
*/
#pragma once

#include <cstdint>
#include <string>

namespace Library
{
	/**	@class DefaultHashFunctor
	*	@brief Functor for default hashing for HashMap. 
	* Hashes use the mixed case version of Bernstein Hash : hash value = 65 * hash value + item[i]
	*/
	template <typename T>
	class DefaultHashFunctor final
	{
	public:
		/** @brief Default constructor */
		DefaultHashFunctor() = default;
		/** @brief Default destructor */
		~DefaultHashFunctor() = default;

		/** @brief overload of () operator to give hash values for the provided key based on Bernstein hash
		*	@param key
		*	@return hash value
		*/
		std::uint32_t operator()(const T& key) const;
	};
}

#include "DefaultHashFunctor.inl"