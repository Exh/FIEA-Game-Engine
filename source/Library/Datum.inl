/**	@file Datum.inl
*	@brief Templated get implemetations
*/

#include "Datum.h"

namespace Library
{
	template <typename T> T& Datum::Get(std::uint32_t index)
	{
		throw std::exception("Datum type doesn't exist");
	}

	template<> std::int32_t& Datum::Get<std::int32_t>(std::uint32_t index)
	{
		if (mType == DatumType::Unknown)
		{
			std::exception("Datum type is not set");
		}

		if (mType != DatumType::Integer)
		{
			throw std::exception("Datum type is different from the type requested");
		}

		if (index >= mSize)
		{
			throw std::out_of_range("Cant access datum at index " + index);
		}

		return mData.intPtr[index];
	}

	template<> float& Datum::Get<float>(std::uint32_t index)
	{
		if (mType == DatumType::Unknown)
		{
			std::exception("Datum type is not set");
		}

		if (mType != DatumType::Float)
		{
			throw std::exception("Datum type is different from the type requested");
		}

		if (index >= mSize)
		{
			throw std::out_of_range("Cant access datum at index " + index);
		}

		return mData.floatPtr[index];
	}

	template<> glm::vec4& Datum::Get<glm::vec4>(std::uint32_t index)
	{
		if (mType == DatumType::Unknown)
		{
			std::exception("Datum type is not set");
		}

		if (mType != DatumType::Vector)
		{
			throw std::exception("Datum type is different from the type requested");
		}

		if (index >= mSize)
		{
			throw std::out_of_range("Cant access datum at index " + index);
		}

		return mData.vec4Ptr[index];
	}

	template<> glm::mat4& Datum::Get<glm::mat4>(std::uint32_t index)
	{
		if (mType == DatumType::Unknown)
		{
			std::exception("Datum type is not set");
		}

		if (mType != DatumType::Matrix)
		{
			throw std::exception("Datum type is different from the type requested");
		}

		if (index >= mSize)
		{
			throw std::out_of_range("Cant access datum at index " + index);
		}

		return mData.mat4Ptr[index];
	}

	template<> std::string& Datum::Get<std::string>(std::uint32_t index)
	{
		if (mType == DatumType::Unknown)
		{
			std::exception("Datum type is not set");
		}

		if (mType != DatumType::String)
		{
			throw std::exception("Datum type is different from the type requested");
		}

		if (index >= mSize)
		{
			throw std::out_of_range("Cant access datum at index " + index);
		}

		return mData.strPtr[index];
	}
}