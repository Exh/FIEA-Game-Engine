/**	@file Datum.cpp
*	@brief Implementa
*/
#include "pch.h"
#include "Datum.h"

namespace Library
{
#pragma region Constructors and Destructor
	Datum::Datum(DatumType type, bool isExternal, std::uint32_t size)
		:mType(DatumType::Unknown), mData(), mSize(0), mCapacity(0), mIsExternal(isExternal)
	{
		if (type != DatumType::Unknown)
		{
			SetType(type);
		}

		if (type!=DatumType::Unknown && !mIsExternal && size != 0 )
		{
			SetSize(size);
		}
	}

	Datum::~Datum()
	{
		Clear();
	}

	Datum::Datum(const Datum& rhs)
		:Datum()
	{
		*this = rhs;
	}

#pragma endregion

#pragma region Clear
	const Datum::ClearFunction Datum::ClearFunctionArray[static_cast<int>(Datum::DatumType::END)] = {
		Datum::ClearInvalid,
		Datum::ClearIntegers,
		Datum::ClearFloats,
		Datum::ClearVector,
		Datum::ClearMatrix,
		Datum::ClearString,
		Datum::ClearPointers,
		Datum::ClearTable
	};

	void Datum::Clear()
	{
		if (!mIsExternal && mSize>0)
		{
			ClearFunctionArray[static_cast<int>(mType)](mData);
		}

		mData.voidPtr = nullptr;
		mSize = 0;
	}

	void Datum::ClearIntegers(DatumValue& value)
	{
		delete[] value.intPtr;
	}

	void Datum::ClearFloats(DatumValue& value)
	{
		delete[] value.floatPtr;
	}

	void Datum::ClearString(DatumValue& value)
	{
		delete[] value.strPtr;
	}

	void Datum::ClearVector(DatumValue& value)
	{
		delete[] value.vec4Ptr;
	}

	void Datum::ClearMatrix(DatumValue& value)
	{
		delete[] value.mat4Ptr;
	}

	void Datum::ClearPointers(DatumValue& value)
	{
		delete[] value.rttiPtr;
	}

	void Datum::ClearTable(DatumValue& value)
	{
		delete[] value.tablePtr;
	}

	void Datum::ClearInvalid(DatumValue& value)
	{
		throw std::exception("Invalid operation");
	}

#pragma endregion

#pragma region Operator =
	 const Datum::CopyFunction Datum::CopyFunctionArray[static_cast<int>(DatumType::END)]={
		 Datum::CopyInvalid,
		 Datum::CopyIntegers,
		 Datum::CopyFloats,
		 Datum::CopyVectors,
		 Datum::CopyMatrices,
		 Datum::CopyStrings,
		 Datum::CopyPointers,
		 Datum::CopyInvalid
	 };

	Datum& Datum::operator=(const Datum& rhs)
	{
		if (this != &rhs)
		{
			//if it's already internal clear existing data
			if (!mIsExternal)
			{
				Clear();
			}
			
			mIsExternal = rhs.mIsExternal;
			mType = rhs.mType;


			//if rhs is external, shallow copy the pointers
			if (rhs.mIsExternal)
			{
				mData.voidPtr = rhs.mData.voidPtr;
				mSize = rhs.mSize;
				mCapacity = rhs.mCapacity;
			}
			else
			{
				SetSize(rhs.mSize);

				CopyFunctionArray[static_cast<int>(mType)](mData, rhs.mData,rhs.mSize);
			}
		}

		return *this;
	}

	void Datum::CopyIntegers(DatumValue& lhs, const DatumValue& rhs,std::uint32_t size)
	{
		for (std::uint32_t i = 0; i < size; ++i)
		{
			lhs.intPtr[i] = rhs.intPtr[i];
		}
	}

	void Datum::CopyFloats(DatumValue& lhs, const DatumValue& rhs,std::uint32_t size)
	{
		for (std::uint32_t i = 0; i < size; ++i)
		{
			lhs.floatPtr[i] = rhs.floatPtr[i];
		}
	}

	void Datum::CopyVectors(DatumValue& lhs, const DatumValue& rhs,std::uint32_t size)
	{
		for (std::uint32_t i = 0; i < size; ++i)
		{
			lhs.vec4Ptr[i] = rhs.vec4Ptr[i];
		}
	}

	void Datum::CopyMatrices(DatumValue& lhs, const DatumValue& rhs,std::uint32_t size)
	{
		for (std::uint32_t i = 0; i < size; ++i)
		{
			lhs.mat4Ptr[i] = rhs.mat4Ptr[i];
		}
	}

	void Datum::CopyPointers(DatumValue& lhs, const DatumValue& rhs,std::uint32_t size)
	{
		for (std::uint32_t i = 0; i < size; ++i)
		{
			lhs.rttiPtr[i] = rhs.rttiPtr[i];
		}
	}

	void Datum::CopyInvalid(DatumValue& lhs, const DatumValue& rhs,std::uint32_t size)
	{
		lhs.voidPtr = rhs.voidPtr;
	}

	void Datum::CopyStrings(DatumValue& lhs, const DatumValue& rhs,std::uint32_t size)
	{
		for (std::uint32_t i = 0; i < size; ++i)
		{
			lhs.strPtr[i] = rhs.strPtr[i];
		}
	}

	void Datum::InitScalarAssignment(DatumType assignedType)
	{
		if (mType == DatumType::Unknown)
		{
			mType = assignedType;
		}

		if (mType != assignedType)
		{
			throw std::exception("Datum type mismatch");
		}
	}

	Datum& Datum::operator=(const std::int32_t& rhs)
	{
		if (mData.intPtr != &rhs)
		{
			InitScalarAssignment(DatumType::Integer);

			if (!mIsExternal)
			{
				SetSize(1);
			}
			else
			{
				if (mSize == 0)
				{
					std::exception("Storage not set");
				}
			}

			mData.intPtr[0] = rhs;
		}
		return *this;
	}

	Datum& Datum::operator=(const float& rhs)
	{
		if (mData.floatPtr != &rhs)
		{
			InitScalarAssignment(DatumType::Float);

			if (!mIsExternal)
			{
				SetSize(1);
			}
			else
			{
				if (mSize == 0)
				{
					throw std::exception("Storage not set");
				}
			}

			mData.floatPtr[0] = rhs;
		}
		return *this;
	}

	Datum& Datum::operator=(const glm::vec4& rhs)
	{
		if (mData.vec4Ptr != &rhs)
		{
			InitScalarAssignment(DatumType::Vector);

			if (!mIsExternal)
			{
				SetSize(1);
			}
			else
			{
				if (mSize == 0)
				{
					std::exception("Storage not set");
				}
			}

			mData.vec4Ptr[0] = rhs;
		}
		return *this;
	}

	Datum& Datum::operator=(const glm::mat4& rhs)
	{
		if (mData.mat4Ptr != &rhs)
		{
			InitScalarAssignment(DatumType::Matrix);

			if (!mIsExternal)
			{
				SetSize(1);
			}
			else
			{
				if (mSize == 0)
				{
					std::exception("Storage not set");
				}
			}

			mData.mat4Ptr[0] = rhs;
		}		return *this;
	}

	Datum& Datum::operator=(const std::string& rhs)
	{
		if (mData.strPtr != &rhs)
		{
			InitScalarAssignment(DatumType::String);

			if (!mIsExternal)
			{
				SetSize(1);
			}
			else
			{
				if (mSize == 0)
				{
					std::exception("Storage not set");
				}
			}

			mData.strPtr[0] = rhs;
		}
		return *this;
	}

	Datum& Datum::operator=(RTTI* rhs)
	{
		if (mData.rttiPtr != &rhs)
		{
			InitScalarAssignment(DatumType::Pointer);

			if (rhs == nullptr)
			{
				throw std::exception("Null data");
			}

			if (!mIsExternal)
			{
				SetSize(1);
			}
			else
			{
				if (mSize == 0)
				{
					std::exception("Storage not set");
				}
			}

			mData.rttiPtr[0] = rhs;
		}
		return *this; 
	}

	Datum& Datum::operator=(Scope* rhs)
	{
		if (mData.tablePtr != &rhs)
		{
			InitScalarAssignment(DatumType::Table);

			if (rhs == nullptr)
			{
				throw std::exception("Null data");
			}

			if (!mIsExternal)
			{
				SetSize(1);
			}
			else
			{
				if (mSize == 0)
				{
					std::exception("Storage not set");
				}
			}

			mData.tablePtr[0] = rhs;
		}
		return *this;
	}
#pragma endregion

#pragma region Set Get 
	bool Datum::IsExternal() const
	{
		return mIsExternal;
	}

	Datum::DatumType Datum::GetType() const
	{
		return mType;
	}

	void Datum::SetType(const DatumType& type)
	{
		if (mType != DatumType::Unknown && type!=mType)
		{
			throw std::exception("Type of Datum is already set");
		}

		if (type == DatumType::Unknown)
		{
			throw std::exception("Invalid type");
		}

		mType = type;
	}

	std::uint32_t Datum::Size() const
	{
		return mSize;
	}

	std::uint32_t Datum::Capacity() const
	{
		return mCapacity;
	}
#pragma endregion

#pragma region Set Size
	const Datum::ReserveFunction Datum::ReserveFunctionArray[static_cast<int>(Datum::DatumType::END)] = {
		Datum::ReserveInvalid,
		Datum::ReserveIntegers,
		Datum::ReserveFloats,
		Datum::ReserveVectors,
		Datum::ReserveMatrices,
		Datum::ReserveString,
		Datum::ReservePointers,
		Datum::ReserveTables
	};

	void Datum::SetSize(std::uint32_t newSize)
	{	
		if (mIsExternal)
		{
			throw std::exception("Cant set size on an external datum");
		}

		if (newSize > mCapacity)
		{
			ReserveFunctionArray[static_cast<int>(mType)](*this, newSize);
			mCapacity = newSize;
		}
		
		mSize = newSize;
	}

	void Datum::ReserveIntegers(Datum& lhs, std::uint32_t size)
	{
		//Reserve new
		std::int32_t* newValues = new std::int32_t[size]();

		//copy the old values existing into new, if they exist
		for (std::uint32_t i = 0; i < lhs.mSize; i++)
		{
			newValues[i] = lhs.mData.intPtr[i];
		}

		//clear the old values and point to new array
		lhs.Clear();
		lhs.mData.intPtr = newValues;
	}
	
	void Datum::ReserveFloats(Datum& lhs, std::uint32_t size)
	{
		float* newValues = new float[size]();

		for (std::uint32_t i = 0; i < lhs.mSize; i++)
		{
			newValues[i] = lhs.mData.floatPtr[i];
		}

		lhs.Clear();
		lhs.mData.floatPtr = newValues;
	}

	void Datum::ReserveVectors(Datum& lhs, std::uint32_t size)
	{
		glm::vec4* newValues = new glm::vec4[size]();

		for (std::uint32_t i = 0; i < lhs.mSize; i++)
		{
			newValues[i] = lhs.mData.vec4Ptr[i];
		}

		lhs.Clear();
		lhs.mData.vec4Ptr = newValues;
	}

	void Datum::ReserveMatrices(Datum& lhs, std::uint32_t size)
	{
		glm::mat4* newValues = new glm::mat4[size]();

		for (std::uint32_t i = 0; i < lhs.mSize; i++)
		{
			newValues[i] = lhs.mData.mat4Ptr[i];
		}

		lhs.Clear();
		lhs.mData.mat4Ptr = newValues;
	}

	void Datum::ReservePointers(Datum& lhs, std::uint32_t size)
	{
		RTTI** newValues = new RTTI*[size]();

		for (std::uint32_t i = 0; i < lhs.mSize; i++)
		{
			newValues[i] = lhs.mData.rttiPtr[i];
		}

		lhs.Clear();
		lhs.mData.rttiPtr = newValues;
	}

	void Datum::ReserveString(Datum& lhs, std::uint32_t size)
	{
		std::string* newValues = new std::string[size]();

		for (std::uint32_t i = 0; i < lhs.mSize; i++)
		{
			newValues[i] = lhs.mData.strPtr[i];
		}

		lhs.Clear();
		lhs.mData.strPtr = newValues;
	}

	void Datum::ReserveInvalid(Datum& lhs, std::uint32_t size)
	{
		throw std::exception("Invalid operation");
	}

	void Datum::ReserveTables(Datum& lhs, std::uint32_t size)
	{
		Scope** newValues = new Scope*[size]();

		for (std::uint32_t i = 0; i < lhs.mSize; i++)
		{
			newValues[i] = lhs.mData.tablePtr[i];
		}

		lhs.Clear();
		lhs.mData.tablePtr = newValues;
	}
#pragma endregion	

#pragma region SetStorage
	void  Datum::InitSetStorage(DatumType assignedType)
	{
		//cant set storage on internal
		if (!mIsExternal && mSize>0)
		{
			throw std::exception("Cant set storage on an internal datum");
		}

		//I'm not allowing datum type to change, in order to avoid confusion when trying to reuse datums later
		//but I'm allowing the same datum to change to other storages of same type or resize the same storage
		if (mType == DatumType::Unknown)
		{
			mType = assignedType;
		}

		if (mType != assignedType)
		{
			throw std::exception("Cant change datum type");
		}
	}

	void Datum::SetStorage(std::int32_t* data, std::uint32_t size)
	{
		InitSetStorage(DatumType::Integer);
		
		if (data == nullptr)
		{
			throw std::exception("Data is empty"); 
		}

		mData.intPtr = data;
		mSize = size;
		mCapacity = size;
		mIsExternal = true;
	}
	
	void Datum::SetStorage(float* data, std::uint32_t size)
	{
		InitSetStorage(DatumType::Float);

		if (data == nullptr)
		{
			throw std::exception("Data is empty");
		}

		mData.floatPtr = data;
		mSize = size;
		mCapacity = size;
		mIsExternal = true;
	}

	void Datum::SetStorage(glm::vec4* data, std::uint32_t size)
	{
		InitSetStorage(DatumType::Vector);

		if (data == nullptr)
		{
			throw std::exception("Data is empty");
		}

		mData.vec4Ptr = data;
		mSize = size;
		mCapacity = size;
		mIsExternal = true;
	}

	void Datum::SetStorage(glm::mat4* data, std::uint32_t size)
	{
		InitSetStorage(DatumType::Matrix);

		if (data == nullptr)
		{
			throw std::exception("Data is empty");
		}

		mData.mat4Ptr = data;
		mSize = size;
		mCapacity = size;
		mIsExternal = true;
	}

	void Datum::SetStorage(std::string* data, std::uint32_t size)
	{
		InitSetStorage(DatumType::String);

		if (data == nullptr)
		{
			throw std::exception("Data is empty");
		}

		mData.strPtr = data;
		mSize = size;
		mCapacity = size;
		mIsExternal = true;
	}

	void Datum::SetStorage(RTTI** data, std::uint32_t size)
	{
		InitSetStorage(DatumType::Pointer);

		if (data == nullptr)
		{
			throw std::exception("Data is empty");
		}

		mData.rttiPtr = data;
		mSize = size;
		mCapacity = size;
		mIsExternal = true;
	}

	void Datum::SetStorage(Scope** data, std::uint32_t size)
	{
		InitSetStorage(DatumType::Table);

		if (data == nullptr)
		{
			throw std::exception("Data is empty");
		}

		mData.tablePtr = data;
		mSize = size;
		mCapacity = size;
		mIsExternal = true;
	}
#pragma endregion

#pragma region Operator == !=
	const Datum::EqualityFunction Datum::EqualityFunctionArray[static_cast<int>(DatumType::END)] = {
		Datum::EqualityInvalid,
		Datum::EqualityIntegers,
		Datum::EqualityFloats,
		Datum::EqualityVectors,
		Datum::EqualityMatrices,
		Datum::EqualityString,
		Datum::EqualityPointers,
		Datum::EqualityTables
	};

	bool Datum::operator==(const Datum& rhs) const
	{
		bool isEqual=true;

		if (mType != rhs.mType ||  mSize!=rhs.mSize)
		{
			isEqual=false;
		}
		else
		{
			//march through the data and check if they're equal, without consideration for internal or external
			isEqual = EqualityFunctionArray[static_cast<int>(mType)](*this,rhs);
		}

		return isEqual;
	}

	bool Datum::EqualityIntegers(const Datum& lhs, const Datum& rhs)
	{
		for (std::uint32_t i = 0; i < lhs.mSize; ++i)
		{
			if (lhs.mData.intPtr[i] != rhs.mData.intPtr[i])
			{
				return false;
			}
		}

		return true;
	}

	bool Datum::EqualityFloats(const Datum& lhs, const Datum& rhs)
	{
		for (std::uint32_t i = 0; i < lhs.mSize; ++i)
		{
			if (lhs.mData.floatPtr[i] != rhs.mData.floatPtr[i])
			{
				return false;
			}
		}

		return true;
	}

	bool Datum::EqualityVectors(const Datum& lhs, const Datum& rhs)
	{
		for (std::uint32_t i = 0; i < lhs.mSize; ++i)
		{
			if (lhs.mData.vec4Ptr[i] != rhs.mData.vec4Ptr[i])
			{
				return false;
			}
		}

		return true;
	}

	bool Datum::EqualityMatrices(const Datum& lhs, const Datum& rhs)
	{
		for (std::uint32_t i = 0; i < lhs.mSize; ++i)
		{
			if (lhs.mData.mat4Ptr[i] != rhs.mData.mat4Ptr[i])
			{
				return false;
			}
		}

		return true;
	}
	
	bool Datum::EqualityPointers(const Datum& lhs, const Datum& rhs)
	{
		for (std::uint32_t i = 0; i < lhs.mSize; ++i)
		{
			if (lhs.mData.rttiPtr[i] != rhs.mData.rttiPtr[i])
			{
				return false;
			}
		}

		return true;
	}
	
	bool Datum::EqualityString(const Datum& lhs, const Datum& rhs)
	{
		for (std::uint32_t i = 0; i < lhs.mSize; ++i)
		{
			if (lhs.mData.strPtr[i] != rhs.mData.strPtr[i])
			{
				return false;
			}
		}

		return true;
	}
	
	bool Datum::EqualityInvalid(const Datum& lhs, const Datum& rhs)
	{
		//both of type unknown and of same size but just empty
		if (lhs.Size() == 0 && rhs.Size() == 0)
		{
			return true;
		}

		//return (lhs.mData.voidPtr == rhs.mData.voidPtr); -> doesnt make sense to compare these
		return false; 
	}

	bool Datum::EqualityTables(const Datum& lhs, const Datum& rhs)
	{
		for (std::uint32_t i = 0; i < lhs.mSize; ++i)
		{
			if (*(lhs.mData.tablePtr[i]) != *(rhs.mData.tablePtr[i]))
			{
				return false;
			}
		}

		return true;
	}

	//Scalars
	bool Datum::operator==(const std::int32_t& rhs) const
	{
		if (mType != DatumType::Integer)
		{
			return false;
		}

		if (mSize == 0)
		{
			return true;
		}

		return mData.intPtr[0] == rhs;
	}

	bool Datum::operator==(const float& rhs) const
	{
		if (mType != DatumType::Float)
		{
			return false;
		}

		if (mSize == 0)
		{
			return true;
		}

		return mData.floatPtr[0] == rhs;
	}

	bool Datum::operator==(const glm::vec4& rhs) const
	{
		if (mType != DatumType::Vector)
		{
			return false;
		}

		if (mSize == 0)
		{
			return true;
		}

		return mData.vec4Ptr[0] == rhs;
	}

	bool Datum::operator==(const glm::mat4& rhs) const
	{
		if (mType != DatumType::Matrix)
		{
			return false;
		}

		if (mSize == 0)
		{
			return true;
		}

		return mData.mat4Ptr[0] == rhs;
	}

	bool Datum::operator==(const std::string& rhs) const
	{
		if (mType != DatumType::String)
		{
			return false;
		}

		if (mSize == 0)
		{
			return true;
		}

		return mData.strPtr[0] == rhs;
	}

	bool Datum::operator==(RTTI* rhs) const
	{
		if (mType != DatumType::Pointer)
		{
			return false;
		}

		if (mSize == 0)
		{
			return true;
		}

		return mData.rttiPtr[0] == rhs;
	}

	/*bool Datum::operator==(Scope* rhs) const
	{
		if (mType != DatumType::Table)
		{
			return false;
		}

		if (mSize == 0)
		{
			return true;
		}

		return (mData.tablePtr[0] == rhs);
	}*/

	bool Datum::operator!=(const Datum& rhs) const
	{
		return !(*this == rhs);
	}

	bool Datum::operator!=(const std::int32_t& rhs) const
	{
		return !(operator==(rhs));
	}

	bool Datum::operator!=(const float& rhs) const
	{
		return !(operator==(rhs));
	}

	bool Datum::operator!=(const glm::vec4& rhs) const
	{
		return !(operator==(rhs));
	}

	bool Datum::operator!=(const glm::mat4& rhs) const
	{
		return !(operator==(rhs));
	}

	bool Datum::operator!=(const std::string& rhs) const
	{
		return !(operator==(rhs));
	}

	bool Datum::operator!=(RTTI* rhs) const
	{
		return !(operator==(rhs));
	}

	bool Datum::operator!=(Scope* rhs) const
	{
		return !(operator==(rhs));
	}
#pragma endregion

#pragma region Set
	void Datum::InitSet(DatumType assignedType)
	{
		if (mType == DatumType::Unknown)
		{
			mType = assignedType;
		}

		//Chose to throw an exception instead of asserting
		if (mType != assignedType)
		{
			throw std::exception("Datum type mismatch");
		}
	}

	void Datum::Set(const std::int32_t& value, std::uint32_t index)
	{	
		InitSet(DatumType::Integer);

		if (index == UINT32_MAX)
		{
			index = mSize;
		}

		if (index>=mSize)
		{
			if (!mIsExternal)
			{
				SetSize(index+1);
			}
			else
			{
				throw std::out_of_range("Datum out of bounds");
			}
		}

		mData.intPtr[index] = value;
	}

	void Datum::Set(const float& value, std::uint32_t index)
	{
		InitSet(DatumType::Float);

		if (index == UINT32_MAX)
		{
			index = mSize;
		}

		if (index >= mSize)
		{
			if (!mIsExternal)
			{
				SetSize(index + 1);
			}
			else
			{
				throw std::out_of_range("Datum out of bounds");
			}
		}

		mData.floatPtr[index] = value;

	}

	void Datum::Set(const glm::vec4& value, std::uint32_t index)
	{
		InitSet(DatumType::Vector);

		if (index == UINT32_MAX)
		{
			index = mSize;
		}

		if (index >= mSize)
		{
			if (!mIsExternal)
			{
				SetSize(index + 1);
			}
			else
			{
				throw std::out_of_range("Datum out of bounds");
			}
		}

		mData.vec4Ptr[index] = value;
	}

	void Datum::Set(const glm::mat4& value, std::uint32_t index)
	{
		InitSet(DatumType::Matrix);

		if (index == UINT32_MAX)
		{
			index = mSize;
		}

		if (index >= mSize)
		{
			if (!mIsExternal)
			{
				SetSize(index + 1);
			}
			else
			{
				throw std::out_of_range("Datum out of bounds");
			}
		}

		mData.mat4Ptr[index] = value;
	}

	void Datum::Set(const std::string& value, std::uint32_t index)
	{
		InitSet(DatumType::String);

		if (index == UINT32_MAX)
		{
			index = mSize;
		}

		if (index >= mSize)
		{
			if (!mIsExternal)
			{
				SetSize(index + 1);
			}
			else
			{
				throw std::out_of_range("Datum out of bounds");
			}
		}

		mData.strPtr[index] = value;
	}
	
	void Datum::Set(RTTI* value, std::uint32_t index)
	{
		InitSet(DatumType::Pointer);

		if (value != nullptr)
		{
			if (index == UINT32_MAX)
			{
				index = mSize;
			}

			if (index >= mSize)
			{
				if (!mIsExternal)
				{
					SetSize(index + 1);
				}
				else
				{
					throw std::out_of_range("Datum out of bounds");
				}
			}

			mData.rttiPtr[index] = value;
		}
	}

	void Datum::Set(Scope* value, std::uint32_t index)
	{
		InitSet(DatumType::Table);

		if (value != nullptr)
		{
			if (index == UINT32_MAX)
			{
				index = mSize;
			}

			if (index >= mSize)
			{
				if (!mIsExternal)
				{
					SetSize(index + 1);
				}
				else
				{
					throw std::out_of_range("Datum out of bounds");
				}
			}

			//mData.tablePtr[index] = value;
			Insert(value, index);
		}
	}
#pragma endregion

#pragma region String Functions
	void Datum::SetFromString(const std::string& value, std::uint32_t index)
	{
		switch (mType)
		{
		case DatumType::Integer:
			Set(std::stoi(value), index);
			break;

		case DatumType::Float:
			Set(std::stof(value), index);
			break;

		case DatumType::String:
			Set(value, index);
			break;

		case DatumType::Vector:
		{
			//glm vector to_string format : fvec4(v1, v2, v3, v4)
			//my format : (v1,v2,v3,v4)

			//remove fvec4
			//value.erase(0, std::string("fvec4").length());
			std::string copy = value;

			//remove other unwanted characters
			std::string charsToRemove = "() ";
			for (std::uint32_t i = 0; i < charsToRemove.length(); i++)
			{
				copy.erase(std::remove(copy.begin(), copy.end(), charsToRemove[i]), copy.end());
			}

			glm::vec4 newVec4(0);
			int i = 0;

			std::stringstream sstream(copy);
			std::string extract;

			//get every part of string separated by space, parse it to float
			//and assign it to vector
			while (std::getline(sstream, extract, ','))
			{
				newVec4[i++] = std::stof(extract);

				//don't read extra data
				if (i >= 4)
				{
					break;
				}
			}


			//if only one value, default construct with that value
			if (i == 1)
			{
				newVec4 = glm::vec4(newVec4[0]);
			}
			//default to 0 if not enough
			else if (i < 4)
			{
				//throw std::invalid_argument("Not enough data in string");
				while (i<4)
				{
					newVec4[i++] = 0;
				}
			}

			Set(newVec4, index);
		}
			break;

		case DatumType::Matrix:
		{
			//glm mat4 to_string format : mat4x4((r1v1, r1v2, r1v3, r1v4), (r2v1.......))
			//my format ((r1v1, r1v2, r1v3, r1v4), (r2v1.......))

			//remove mat4x4
			//value.erase(0, std::string("mat4x4").length());

			std::string copy = value;

			//remove other unwanted characters
			std::string charsToRemove = "() ";
			for (std::uint32_t i = 0; i < charsToRemove.length(); ++i)
			{
				copy.erase(std::remove(copy.begin(), copy.end(), charsToRemove[i]), copy.end());
			}

			glm::mat4 newMat4(0);
			std::uint32_t i = 0;
			std::uint32_t j = 0;

			std::stringstream sstream(copy);
			std::string extract;

			//get each part of string separated by space, parse it into a float
			//and assign it to matrix
			while (std::getline(sstream, extract, ','))
			{
				newMat4[i][j] = std::stof(extract);
				
				//if the columns are full, goto next row
				++j;
				if (j >= 4)
				{
					++i;
					j = 0;

					//dont read extra data
					if (i >= 4)
					{
						break;
					}
				}
			}

			//if only one value, construct a matrix with that
			if (i == 0 && j == 1)
			{
				newMat4 = glm::mat4(newMat4[0][0]);
			}
			//default to 0 if not enough values
			else if (i < 4)
			{
				//throw std::invalid_argument("Not enough data in string");

				while (i < 4)
				{
					newMat4[i][j] = 0;

					++j;
					if (j >= 4)
					{
						++i;
						j = 0;
					}
				}
			}
			
			Set(newMat4, index);
		}
			break;

		default:
			throw std::exception("Invalid datum type");
		}
	}

	void Datum::TrySetFromString(const std::string& value, std::uint32_t index, bool throwException)
	{
		try
		{
			SetFromString(value, index);
		}
		catch (std::exception)
		{
			if (throwException)
			{
				throw;
			}
			else
			{
				//set default values if the user doesnt want an exception
				switch (mType)
				{
				case DatumType::Integer:
					Set(0, index);
					break;

				case DatumType::Float:
					Set(0.0f, index);
					break;

				case DatumType::Vector:
					Set(glm::vec4(0), index);
					break;

				case DatumType::Matrix:
					Set(glm::mat4(0), index);
					break;

				case DatumType::String:
					Set("", index);
					break;

				default:
					throw std::exception("Invalid datum type");
					break;
				}
			}
		}
	}

	std::string Datum::ToString(std::uint32_t index) const
	{
		switch (mType)
		{
		case DatumType::Integer:
			return std::to_string(mData.intPtr[index]);

		case DatumType::Float:
			return std::to_string(mData.floatPtr[index]);

		case DatumType::String:
			return mData.strPtr[index];

		case DatumType::Vector:
		{
			std::string vecString = glm::to_string(mData.vec4Ptr[index]);
			//remove fvec4
			vecString.erase(0, std::string("fvec4").length());
			return vecString;
		}

		case DatumType::Matrix:
		{
			std::string matString = glm::to_string(mData.mat4Ptr[index]);
			//remove mat4x4
			matString.erase(0, std::string("mat4x4").length());
			return matString;
		}

		default:
			throw std::exception("Invalid datum type");
		}
	}
#pragma endregion

#pragma region Get
	RTTI* Datum::GetPointer(std::uint32_t index)
	{
		if (mType == DatumType::Unknown)
		{
			std::exception("Datum type is not set");
		}

		if (mType != DatumType::Pointer)
		{
			throw std::exception("Datum type is different from the type requested");
		}

		if (index >= mSize)
		{
			throw std::out_of_range("Cant access datum at index " + index);
		}

		return mData.rttiPtr[index];
	}

	Scope* Datum::GetTable(std::uint32_t index)
	{
		if (mType == DatumType::Unknown)
		{
			std::exception("Datum type is not set");
		}

		if (mType != DatumType::Table)
		{
			throw std::exception("Datum type is different from the type requested");
		}

		if (index == UINT32_MAX)
		{
			index = mSize - 1;
		}

		if (index >= mSize)
		{
			throw std::out_of_range("Cant access datum at index " + index);
		}

		return mData.tablePtr[index];
	}
#pragma endregion

#pragma region Scope functions
	Scope& Datum::operator[](std::uint32_t index)
	{
		if (mType != DatumType::Table)
		{
			throw std::exception("Invalid operation");
		}

		return *GetTable(index);
	}

	void Datum::PushBack(Scope* child)
	{
		if (child != nullptr)
		{
			if (mType != DatumType::Table)
			{
				throw std::exception("Invalid type");
			}
			else if (mIsExternal)
			{
				throw std::exception("Cant insert in an external datum");
			}

			bool foundEmptySpot = false;
			std::uint32_t emptyIndex;

			//iterate through and find an empty spot
			for (emptyIndex = 0; emptyIndex < mSize; emptyIndex++)
			{
				if (mData.tablePtr[emptyIndex] == nullptr)
				{
					foundEmptySpot = true;
					break;
				}
			}

			//if there is one insert there
			if (foundEmptySpot)
			{
				mData.tablePtr[emptyIndex] = child;
			}
			else
			{
				if (mSize + 1 > mCapacity)
				{
					SetSize(mCapacity + 1);
				}

				mData.tablePtr[mSize++] = child;
			}
		}
	}

	std::uint32_t Datum::FindNestedScope(const Scope& child, Datum** foundDatum)
	{
		if (mType != DatumType::Table)
		{
			throw std::exception("Invalid operation");
		}

		//iterate through and find child
		for (std::uint32_t i = 0; i < mSize; i++)
		{
			if (mData.tablePtr[i] == &child)
			{
				if (foundDatum != nullptr)
				{
					*foundDatum = this;
				}
				return i;
			}
		}

		//if not return size and nullptr
		if (foundDatum != nullptr)
		{
			*foundDatum = nullptr;
		}
		return mSize;
	}

	bool Datum::AbandonChild(const Scope& child)
	{
		/*if (child == nullptr)
		{
			throw std::exception("No child to abandon");
		}*/

		if (mType != DatumType::Table)
		{
			throw std::exception("Invalid operation");
		}

		std::uint32_t index = FindNestedScope(child);
		
		if (index < mSize)
		{
			mData.tablePtr[index] = nullptr;
			return true;
		}

		return false;
	}

	void Datum::Insert(Scope* child, std::uint32_t index)
	{
		if (child != nullptr)
		{
			if (mType != DatumType::Table)
			{
				throw std::exception("Invalid type");
			}

			if (mIsExternal)
			{
				throw std::exception("Cant insert in external datum");
			}

			if (mSize + 1 > mCapacity)
			{
				SetSize(mSize + 1);
			}

			if (index >= mSize)
			{
				PushBack(child);
			}
			else
			{
				for (std::uint32_t i = mSize - 1; i < index; i--)
				{
					mData.tablePtr[i] = mData.tablePtr[i - 1];
				}
				mData.tablePtr[index] = child;
			}
		}
	}
}
#pragma endregion