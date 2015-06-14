/**	@file FooFunctor.h
*	@brief contains class definition custom reserve functor for vector
*/
#pragma once

namespace Test
{
	/**	@brief Custom Reserve Scheme that grows capacity by 3 */
	class FooFunctor final
	{
	public:
		/**	@brief Overloading the () operator for functor 
		*	@param size of the vector
		*	@param capacity of the vector
		*	@return capacity+3
		*/
		unsigned int operator()(unsigned int size, unsigned int capacity) const;
	};
}
