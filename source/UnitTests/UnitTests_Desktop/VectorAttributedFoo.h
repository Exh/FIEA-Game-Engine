/**	@file VectorAttributedFoo.h
*	@brief Definition of VectorAttributedFoo
*/
#pragma once

#include "Attributed.h"
#include "pch.h"

using namespace Library;

namespace Test
{
	class VectorAttributedFoo final : public Attributed
	{
		RTTI_DECLARATIONS(VectorAttributedFoo, Attributed)

	public:
		VectorAttributedFoo();
		virtual ~VectorAttributedFoo();

		//public for testing
		std::uint32_t* mExtInt;
		float* mExtFloat;
		std::string* mExtString;
		glm::vec4* mExtVec4;
		glm::mat4* mExtMat4;
		RTTI* mExtRTTI;
		Scope* mExtScope;

		VectorAttributedFoo(const VectorAttributedFoo& rhs);
		VectorAttributedFoo& operator=(const VectorAttributedFoo& rhs);
	};
}
