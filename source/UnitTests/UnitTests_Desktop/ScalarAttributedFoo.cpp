/**	@file ScalarAttributedFoo.cpp
*	@brief Implementation of ScalarAttributedFoo
*/

#include "pch.h"
#include "ScalarAttributedFoo.h"
#include "AnotherFoo.h"

namespace Test
{
	RTTI_DEFINITIONS(ScalarAttributedFoo)

	ScalarAttributedFoo::ScalarAttributedFoo()
	{
		INIT_SIGNATURES

		EXTERNAL_ATTRIBUTE("Ext int", Datum::DatumType::Integer, &mExtInt, 1)
		EXTERNAL_ATTRIBUTE("Ext float", Datum::DatumType::Float, &mExtFloat, 1)
		EXTERNAL_ATTRIBUTE("Ext string", Datum::DatumType::String, &mExtString, 1)
		EXTERNAL_ATTRIBUTE("Ext vec4", Datum::DatumType::Vector, &mExtVec4, 1)
		EXTERNAL_ATTRIBUTE("Ext mat4", Datum::DatumType::Matrix, &mExtMat4, 1)
		EXTERNAL_ATTRIBUTE("Ext rtti", Datum::DatumType::Pointer, &mExtRTTI, 1)
		EXTERNAL_ATTRIBUTE("Ext scope", Datum::DatumType::Table, &mExtScope, 1)

		int intValue = 10;
		INTERNAL_ATTRIBUTE("Int int", Datum::DatumType::Integer, &intValue, 1)

		float floatValue = 0.0f;
		INTERNAL_ATTRIBUTE("Int float", Datum::DatumType::Float, &floatValue, 1)

		std::string strValue = "empty";
		INTERNAL_ATTRIBUTE("Int string", Datum::DatumType::String, &strValue, 1)

		glm::vec4 vecValue = glm::vec4(0);
		INTERNAL_ATTRIBUTE("Int vec4", Datum::DatumType::Vector, &vecValue, 1)
			
		glm::mat4 matValue = glm::mat4(0);
		INTERNAL_ATTRIBUTE("Int mat4", Datum::DatumType::Matrix, &matValue, 1)

		AnotherFoo foo;
		INTERNAL_ATTRIBUTE("Int rtti", Datum::DatumType::Pointer, &foo, 1)

		Scope scope;
		INTERNAL_ATTRIBUTE("Int scope", Datum::DatumType::Table, &scope, 1)

		Populate();
	}

	ScalarAttributedFoo::ScalarAttributedFoo(const ScalarAttributedFoo& rhs)
	{
		*this = rhs;
	}

	ScalarAttributedFoo& ScalarAttributedFoo::operator=(const ScalarAttributedFoo& rhs)
	{
		if (*this != rhs)
		{
			mExtInt = rhs.mExtInt;
			mExtFloat = rhs.mExtFloat;
			mExtString = rhs.mExtString;
			mExtVec4 = rhs.mExtVec4;
			mExtMat4 = mExtMat4;
			mExtRTTI = mExtRTTI;
			mExtScope = mExtScope;

			Attributed::operator=(rhs);
		}

		return *this;
	}
}