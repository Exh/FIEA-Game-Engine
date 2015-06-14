/**	@file AnotherFoo.h
*	@brief Declaration of AnotherFoo
*/
#pragma once
#include "RTTI.h"

namespace Test
{
	/**	@class AnotherFoo
	*	@brief Declaration of user defined temporary class to test RTTI
	*/
	class AnotherFoo final : public Library::RTTI
	{
		RTTI_DECLARATIONS(AnotherFoo, RTTI)

	public:
		/**	@brief Default constructor */
		AnotherFoo();
		/**	@brief Default destructor */
		~AnotherFoo();
	};
}
