#include "pch.h"
#include "VectorAttributedFoo.h"
#include "AnotherFoo.h"

namespace Test
{
	RTTI_DEFINITIONS(VectorAttributedFoo)

	VectorAttributedFoo::VectorAttributedFoo()
	{
		mExtInt = new std::uint32_t[3]();
		mExtFloat = new float[3]();
		mExtString = new std::string[3]();
		mExtVec4 = new glm::vec4[3]();
		mExtMat4 = new glm::mat4[3]();
		mExtRTTI = new AnotherFoo[3]();
		mExtScope = new Scope[3]();

		INIT_SIGNATURES

		mExtString[0] = "a";
		mExtString[1] = "b";
		mExtString[2] = "z";

		EXTERNAL_ATTRIBUTE("Ext int", Datum::DatumType::Integer, mExtInt, 3)
		EXTERNAL_ATTRIBUTE("Ext float", Datum::DatumType::Float, mExtFloat, 3)
		EXTERNAL_ATTRIBUTE("Ext string", Datum::DatumType::String, mExtString, 3)
		EXTERNAL_ATTRIBUTE("Ext vec4", Datum::DatumType::Vector, mExtVec4, 3)
		EXTERNAL_ATTRIBUTE("Ext mat4", Datum::DatumType::Matrix, mExtMat4, 3)
		EXTERNAL_ATTRIBUTE("Ext rtti", Datum::DatumType::Pointer, mExtRTTI, 3)
		EXTERNAL_ATTRIBUTE("Ext scope", Datum::DatumType::Table, mExtScope, 3)

		int intValues[4] = { 1, 2, 3, 4 };
		INTERNAL_ATTRIBUTE("Int int", Datum::DatumType::Integer, &intValues, 4)

		float floatValues[5] = { 0.0f, 1.0f, 2.0f, 3.0f, 4.0f };
		INTERNAL_ATTRIBUTE("Int float", Datum::DatumType::Float, &floatValues, 3)

		std::string strValue[2] = { "hello", "world" };
		INTERNAL_ATTRIBUTE("Int string", Datum::DatumType::String, &strValue, 1)

		glm::vec4 vecValues[3] = { glm::vec4(1), glm::vec4(2), glm::vec4(3) };
		INTERNAL_ATTRIBUTE("Int vec4", Datum::DatumType::Vector, &vecValues, 2)

		glm::mat4 matValues[2] = { glm::mat4(1), glm::mat4(2) };
		INTERNAL_ATTRIBUTE("Int mat4", Datum::DatumType::Matrix, &matValues, 2)

		AnotherFoo foo1;
		AnotherFoo foo2;
		RTTI* rttiValues[2] = { &foo1, &foo2 };
		INTERNAL_ATTRIBUTE("Int rtti", Datum::DatumType::Pointer, &rttiValues, 2)

		Scope scope;
		Scope* scopeValues[1] = { &scope };
		INTERNAL_ATTRIBUTE("Int scope", Datum::DatumType::Table, &scopeValues, 1)

		Populate();
	}

	VectorAttributedFoo::~VectorAttributedFoo()
	{
		delete[] mExtInt;
		delete[] mExtFloat;
		delete[] mExtString;
		delete[] mExtVec4;
		delete[] mExtMat4;
		delete[] mExtRTTI;
		delete[] mExtScope;
	}

	VectorAttributedFoo::VectorAttributedFoo(const VectorAttributedFoo& rhs)
	{
		*this = rhs;
	}

	VectorAttributedFoo& VectorAttributedFoo::operator=(const VectorAttributedFoo& rhs)
	{
		if (*this != rhs)
		{
			Attributed::operator=(rhs);
		}

		return *this;
	}
}