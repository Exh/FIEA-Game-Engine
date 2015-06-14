/**	@file Datum.h
*	@brief Definition of Datum
*/
#pragma once

#include "glm/glm.hpp"
#include <string>
#include <cstdint>

namespace Library
{
	class RTTI;
	class Scope;

	/**	@class Datum
	*	@brief data structure to store run-time polymorphic data
	*/
	class Datum
	{

	public:
		/** @brief Enumeration of possible datum types */
		enum class DatumType
		{
			Unknown,
			Integer,
			Float,
			Vector,
			Matrix,
			String,
			Pointer,
			Table,
			END
		};

		/** @brief Overloaded constructor to initialise members to default */
		explicit Datum(DatumType type=DatumType::Unknown, bool isExternal=false, std::uint32_t size=0);
		
		/** @brief Copy constructor to deep copy internal datums and shallow copy external datums */
		Datum(const Datum& rhs);
		
		/** @brief Default destructor to prevent memory leaks*/
		~Datum();

		/** @brief Releases allocated resources in case of internal datums and resets size */
		void Clear();

		/** @brief Deep copy internal datums and shallow copy external datums
		*	@param the datum to copy
		*	@return reference to this datum
		*	@throws std::exception, if datum type is unknown
		*/
		Datum& operator=(const Datum& rhs);

		/** @brief Set the value of the datum
		*	@param the value to set
		*	@return reference to this datum
		*	@throws std::exception, if datum type dont match, or if storage is not set for external datums
		*/
		Datum& operator=(const std::int32_t& rhs);
		Datum& operator=(const float& rhs);
		Datum& operator=(const glm::vec4& rhs);
		Datum& operator=(const glm::mat4& rhs);
		Datum& operator=(const std::string& rhs);
		Datum& operator=(RTTI* rhs);
		Datum& operator=(Scope* rhs);

		/** @brief Get the datum type
		*	@return datum type
		*/
		DatumType GetType() const;

		/** @brief Set the datum type of the datum
		*	@param new datum type
		*	@throws std::exception, if datum type is already set or if it is set to unknown
		*/
		void SetType(const DatumType& type);

		/** @brief Returns the number of data in the datum
		*	@return size of this datum
		*/
		std::uint32_t Size() const;

		/** @brief Resize an internal datum
		*	@param the new size
		*	@throws std::exception, if datum type is external, or if type is unknown
		*/
		void SetSize(std::uint32_t newSize=0U);

		/** @brief Returns the total amount of elements the datum can hold
		*	@return max size to this datum
		*/
		std::uint32_t Capacity() const;

		/** @brief Returns if the datum is external or internal
		*	@return true if the datum is external, false if it is internal
		*/
		bool IsExternal() const;

		/** @brief Set the data the external datum should reference. The datum could modify the data but not reallocate, resize or delete the data
		*	@param the storage to point to
		*	@throws std::exception, if datum type is internal or if supplied with an incorrect data type storage
		*/
		void SetStorage(std::int32_t* data, std::uint32_t size);
		void SetStorage(float* data, std::uint32_t size);
		void SetStorage(glm::vec4* data, std::uint32_t size);
		void SetStorage(glm::mat4* data, std::uint32_t size);
		void SetStorage(std::string* data, std::uint32_t size);
		void SetStorage(RTTI** data, std::uint32_t size);
		void SetStorage(Scope** data, std::uint32_t size);

		/** @brief Compare two datums based on their size, datum type and finally their data. 
		*	@param the datum to comapre
		*	@return true if the datums have the same size, same datum types and contain the same data in the same order; false, otherwise
		*/
		bool operator==(const Datum& rhs) const;

		/** @brief Compare the first datum value
		*	@param the value to compare
		*	@return true, if the two values are the same; false, otherwise
		*/
		bool operator==(const std::int32_t& rhs) const;
		bool operator==(const float& rhs) const;
		bool operator==(const glm::vec4& rhs) const;
		bool operator==(const glm::mat4& rhs) const;
		bool operator==(const std::string& rhs) const;
		bool operator==(RTTI* rhs) const;
		//bool operator==(Scope* rhs) const;

		/** @brief Check if the two values are not the same
		*	@param the value to compare
		*	@return true if they are equal; false, otherwise
		*/
		bool operator!=(const Datum& rhs) const;
		bool operator!=(const std::int32_t& rhs) const;
		bool operator!=(const float& rhs) const;
		bool operator!=(const glm::vec4& rhs) const;
		bool operator!=(const glm::mat4& rhs) const;
		bool operator!=(const std::string& rhs) const;
		bool operator!=(RTTI* rhs) const;
		bool operator!=(Scope* rhs) const;

		/** @brief Set the value at the given index. If the index is out of bounds for an internal datum, it automatically resizes the datum to accomodate the value
		*	@param the value to set
		*	@param the index to assign at
		*	@throws std::exception, if datum value type doesnt match the datum type
		*	@throws std::out_of_range if trying to set out of bounds on an external datum
		*/
		void Set(const std::int32_t& value, std::uint32_t index = 0U);
		void Set(const float& value, std::uint32_t index = 0U);
		void Set(const glm::vec4& value, std::uint32_t index = 0U);
		void Set(const glm::mat4& value, std::uint32_t index = 0U);
		void Set(const std::string& value, std::uint32_t index = 0U);
		void Set(RTTI* value, std::uint32_t index = 0U);
		void Set(Scope* value, std::uint32_t index = 0U);

		/** @brief Get the value at the specified index
		*	@param the index to retrieve
		*	@return reference to this data
		*	@throws std::exception, if datum type is unknown or if datum type doesnt match the requested type
		*	@throws std::out_of_range if trying to retrive beyond the bounds of the datum
		*/
		template <typename T> T& Get(std::uint32_t index = 0U);
		template<> std::int32_t& Datum::Get(std::uint32_t index);
		template<> float& Datum::Get(std::uint32_t index);
		template<> glm::vec4& Datum::Get(std::uint32_t index);
		template<> glm::mat4& Datum::Get(std::uint32_t index);
		template<> std::string& Datum::Get(std::uint32_t index);
		RTTI* GetPointer(std::uint32_t index = 0U);
		Scope* GetTable(std::uint32_t index = 0U);

		/** @brief Parse the string value based on the datum type and set it at the specified index
		*	@param the string value to parse
		*	@param the index to set at
		*	@throws std::exception, if datum type is unknown or pointer
		*	@throws std::invalid_argument, if the string is not in a valid format for the datum type
		*/
		void SetFromString(const std::string& value, std::uint32_t index = 0U);

		/** @brief Parse the string value based on the datum type and set it at the specified index, without throwing exceptions.
		* In case of exception, the default value is set at the index based on the datum type
		*	@param the string value to parse
		*	@param the index to set at
		*	@param set false (default), if exceptions should not be thrown; true, otherwise
		*	@throws std::exception, if datum type is unknown or pointer
		*	@throws std::invalid_argument, if the string is not in a valid format for the datum type
		*/
		void TrySetFromString(const std::string& value, std::uint32_t index = 0U, bool throwException=false);

		/** @brief Convert the value at the index to string
		*	@param the index to convert
		*	@throws std::exception, if datum type is unknown or pointer
		*/
		std::string ToString(std::uint32_t index = 0U) const;

		/**	@brief Method to push a scope onto an empty spot, if any, or to the back of the array 
		*	@param the address of the child to push
		*	@throws std::exception, if the datum type isn't Table or if the datum is external
		*/
		void PushBack(Scope* child);

		/**	@brief Method to find the given scope in the datum
		*	@return returns the index in the datum if found or size if not found
		*	@param address of the child to find
		*	@param address of the found datum or nullptr otherwise
		*	@throws std::exception if the child is null or if the datum type is not table
		*/
		std::uint32_t FindNestedScope(const Scope& child, Datum** foundDatum = nullptr);

		/**	@brief get the scope at the given index
		*	@param the index to get at
		*	@return reference to the scope at that index
		*	@throws std::exception if the datum type is not Table
		*/
		Scope& operator[](std::uint32_t index);

		/**	@brief Method to null the position the child is in without deleting the child. Call orphan on the child after this to ensure child doesnt still point to parent
		*	@param address of the child to null out
		*	@throws std::exception if the datum type is not Table or if child is null
		*/
		bool AbandonChild(const Scope& child);

		/**	@brief Insert the child at the given index
		*	@param the scope to insert
		*	@param the index to insert at
		*	@throws std::exception if the datum type is not table or if the datum is external
		*/
		void Insert(Scope* child, std::uint32_t index);
		
	private:
		union DatumValue
		{
			void** voidPtr; ///< array of void pointers
			std::int32_t* intPtr;
			float* floatPtr;
			glm::vec4* vec4Ptr;
			glm::mat4* mat4Ptr;
			std::string* strPtr;
			RTTI** rttiPtr; ///< array of rtti ptrs
			Scope** tablePtr;

			DatumValue() :voidPtr(nullptr){}
		};

		DatumType mType;
		DatumValue mData;
		std::uint32_t mSize;
		std::uint32_t mCapacity;
		bool mIsExternal;

		/* Helper function to error check before scalar assignment */
		void InitScalarAssignment(DatumType assignedType);
		/* Helper function to error check before set storage*/
		void InitSetStorage(DatumType assignedType);
		/* Helper function to error check before set */
		void InitSet(DatumType assignedType);

		//function pointer section
		//clear
		typedef void(*ClearFunction) (DatumValue& value);
		static const ClearFunction ClearFunctionArray[static_cast<int>(DatumType::END)];
		static void ClearIntegers(DatumValue& value);
		static void ClearFloats(DatumValue& value);
		static void ClearVector(DatumValue& value);
		static void ClearMatrix(DatumValue& value);
		static void ClearPointers(DatumValue& value);
		static void ClearTable(DatumValue& value);
		static void ClearInvalid(DatumValue& value);
		static void ClearString(DatumValue& value);
		
		//deep copy
		typedef void(*CopyFunction) (DatumValue& lhs, const DatumValue& rhs,std::uint32_t size);
		static const CopyFunction CopyFunctionArray[static_cast<int>(DatumType::END)];
		static void CopyIntegers(DatumValue& lhs, const DatumValue& rhs,std::uint32_t size);
		static void CopyFloats(DatumValue& lhs, const DatumValue& rhs,std::uint32_t size);
		static void CopyVectors(DatumValue& lhs, const DatumValue& rhs,std::uint32_t size);
		static void CopyMatrices(DatumValue& lhs, const DatumValue& rhs,std::uint32_t size);
		static void CopyPointers(DatumValue& lhs, const DatumValue& rhs,std::uint32_t size);
		static void CopyInvalid(DatumValue& lhs, const DatumValue& rhs,std::uint32_t size);
		static void CopyStrings(DatumValue& lhs, const DatumValue& rhs,std::uint32_t size);
		
		//equality comparison
		typedef bool(*EqualityFunction) (const Datum& lhs, const Datum& rhs);
		static const EqualityFunction EqualityFunctionArray[static_cast<int>(DatumType::END)];
		static bool EqualityIntegers(const Datum& lhs, const Datum& rhs);
		static bool EqualityFloats(const Datum& lhs, const Datum& rhs);
		static bool EqualityVectors(const Datum& lhs, const Datum& rhs);
		static bool EqualityMatrices(const Datum& lhs, const Datum& rhs);
		static bool EqualityPointers(const Datum& lhs, const Datum& rhs);
		static bool EqualityString(const Datum& lhs, const Datum& rhs);
		static bool EqualityInvalid(const Datum& lhs, const Datum& rhs);
		static bool EqualityTables(const Datum& lhs, const Datum& rhs);

		//reserve
		typedef void(*ReserveFunction)(Datum& lhs, std::uint32_t size);
		static const ReserveFunction ReserveFunctionArray[static_cast<int>(DatumType::END)];
		static void ReserveIntegers(Datum& lhs, std::uint32_t size);
		static void ReserveFloats(Datum& lhs, std::uint32_t size);
		static void ReserveVectors(Datum& lhs, std::uint32_t size);
		static void ReserveMatrices(Datum& lhs, std::uint32_t size);
		static void ReservePointers(Datum& lhs, std::uint32_t size);
		static void ReserveString(Datum& lhs, std::uint32_t size);
		static void ReserveInvalid(Datum& lhs, std::uint32_t size);
		static void ReserveTables(Datum& lhs, std::uint32_t size);
	};
}

#include "Datum.inl"