/**	@file DefaultHashFunctor.inl
*	@brief Implementation of DefaultHashFunctor
*/
#include "DefaultHashFunctor.h"

namespace Library
{
	template <typename T>
	std::uint32_t DefaultHashFunctor<T>::operator()(const T& key) const
	{
		std::uint32_t hash=0;
		
		const char* data = reinterpret_cast<const char*>(&key); //cast as an array of bytes
		std::uint32_t size = sizeof(data);

		for (std::uint32_t i = 0; i < size; i++)
		{
			hash = hash * 65 + data[i];
		}

		return hash;
	}

	/** @brief specialised functor class for pointer types */
	template <typename T>
	class DefaultHashFunctor<T*>
	{
	public:
		std::uint32_t operator()(const T* key) const
		{
			if (key == nullptr)
			{
				throw std::exception("Key cant be null");
			}

			std::uint32_t hash = 0;

			const char* data = reinterpret_cast<const char*>(key);
			std::uint32_t size = sizeof(data);

			for (std::uint32_t i = 0; i < size; i++)
			{
				hash = hash * 65 + data[i];
			}

			return hash;
		}
	};

	/** @brief specialised functor class for std::string */
	template <>
	class DefaultHashFunctor<std::string>
	{
	public:
		std::uint32_t operator()(const std::string key) const
		{
			std::uint32_t hash = 0;

			std::uint32_t size = key.length();

			for (std::uint32_t i = 0; i < size; i++)
			{
				hash = hash * 65 + key[i];
			}

			return hash;
		}
	};

	/** @brief specialised functor class for char* */
	template <>
	class DefaultHashFunctor<char*>
	{
	public:
		std::uint32_t operator()(const char* key) const
		{
			if (key == nullptr)
			{
				throw std::exception("Key cant be null");
			}

			std::uint32_t hash = 0;

			std::uint32_t size = strlen(key);

			for (std::uint32_t i = 0; i < size; i++)
			{
				hash = hash * 65 + key[i];
			}

			return hash;
		}
	};
}