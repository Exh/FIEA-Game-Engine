/**	@file Factory.h
*	@brief Declaration of Factory
*/

#pragma once
#include "hashmap.h"

namespace Library
{
	/**	@class Factory
	*	@brief An abstract factory class to store and control concrete factories
	*/
	template <typename AbstractProductT>
	class Factory
	{
	public:
		/**	@brief Find the Concrete factory associated with the given name
		*	@param name of the concrete factory to find
		*	@return address of the concrete if found or nullptr
		*/
		static Factory* Find(const std::string& name); //all static methods of factory are not const, since static methods don't get the this pointer

		/**	@brief Create and return the product of the factory
		*	@param name of the concrete factory whose product is required
		*	@return the address of the product of the concrete factory
		*/
		static AbstractProductT* Create(const std::string& name);
		
		/**	@brief Return the iterator to the start of the factories map
		*	@return Iterator to the beginning of the map
		*/
		static typename HashMap<std::string, Factory*>::Iterator begin();

		/**	@brief Return the iterator to the end of the factories map
		*	@return Iterator to the end  of the map
		*/
		static typename HashMap<std::string, Factory*>::Iterator end();
		
		/**	@brief Registers the concrete factory with the abstract factory
		*	@param the factory to register
		*/
		static void Add(Factory& factory);
		
		/**	@brief Removes the concrete factory from the abastract factory
		*	@param the factory to remove
		*/
		static void Remove(const Factory& factory);
		
		/**	@brief Returns if the Abstract fanctory has the specified factory
		*	@param the name of the factory to check
		*	@return true, if the factory is present, false otherwise
		*/
		static bool ContainsFactory(const std::string& name);

		/**	@brief Returns the number of concrete factories registered
		*	@return count of the factories
		*/
		static std::uint32_t FactoryCount();

		/**	@brief Return the class name of the factory
		*	@return class name associated with the factory
		*/
		virtual const std::string& ClassName() const=0;

		/**	@brief Destructor to free up base class memory */
		virtual ~Factory()=default;
	private:
		/**	@brief Create the product of the factory
		*	@return a new instance of the product this factory produces
		*/
		virtual AbstractProductT* Create() const = 0;

		static HashMap<std::string, Factory*> sFactoryMap; ///< hashmap that stores the address of the factories with their names
	};
}

#include "Factory.inl"