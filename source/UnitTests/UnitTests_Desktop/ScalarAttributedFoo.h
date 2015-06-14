/**	@file ScalarAttributedFoo.h
*	@brief Definition of ScalarAttributedFoo
*/
#pragma once

#include "Attributed.h"
#include "pch.h"

using namespace Library;

namespace Test
{
	class ScalarAttributedFoo final : public Attributed
	{
		RTTI_DECLARATIONS(ScalarAttributedFoo, Attributed)

	public:
		ScalarAttributedFoo();
		virtual ~ScalarAttributedFoo() = default;
		
		//public for testing
		std::uint32_t mExtInt;
		float mExtFloat;
		std::string mExtString;
		glm::vec4 mExtVec4;
		glm::mat4 mExtMat4;
		RTTI* mExtRTTI;
		Scope* mExtScope;

		ScalarAttributedFoo(const ScalarAttributedFoo& rhs);
		ScalarAttributedFoo& operator=(const ScalarAttributedFoo& rhs);

	};
}
