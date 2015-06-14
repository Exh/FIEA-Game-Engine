/**	@file DefaultVectorFunctor
*	@brief class definition for the default reserve scheme for Vector
*/
#pragma once

namespace Library
{
	/**	@class DefaultVectorFunctor
	*	@brief contains an overload of () to enable providing the default reserve scheme for Vector
	*/
	class DefaultVectorFunctor final
	{
	public:
		/**	@brief Empty default constructor */
		DefaultVectorFunctor();

		/**	@brief Empty default destructor */
		~DefaultVectorFunctor();

		/**	@brief Overloading the () operator to implement a functor for Vector's reserve scheme
		*	@param the size of the Vector
		*	@param the capacity of the Vector
		*	@return the new capacity for the Vector
		*/
		unsigned int operator()(unsigned int size, unsigned int capacity) const;
	};
}