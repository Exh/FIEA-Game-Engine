/**	@file Factory.inl
*	@brief Definitions of Factory 
*/

#include "Factory.h"

namespace Library
{
	template <typename AbstractProductT>
	HashMap<std::string, Factory<AbstractProductT>*> Factory<AbstractProductT>::sFactoryMap(32);

	//all static methods of factory are not const, since static methods don't get the this pointer
	template <typename AbstractProductT>
	Factory<AbstractProductT>* Factory<AbstractProductT>::Find(const std::string& name) 
	{
		auto it = sFactoryMap.Find(name);

		if (it != sFactoryMap.end())
		{
			return (*it).second;
		}
		//return the factory only if present
		/*if (sFactoryMap.ContainsKey(name))
		{
			return sFactoryMap[name];
		}*/

		return nullptr;
	}

	template <typename AbstractProductT>
	AbstractProductT* Factory<AbstractProductT>::Create(const std::string& name) 
	{
		Factory* factory = Find(name); //try and find the factory
		//create only if found
		if (factory!=nullptr) 
		{
			return factory->Create();
		}

		return nullptr;
	}

	template <typename AbstractProductT>
	typename HashMap<std::string, Factory<AbstractProductT>*>::Iterator Factory<AbstractProductT>::begin() 
	{
		return sFactoryMap.begin();
	}

	template <typename AbstractProductT>
	typename HashMap<std::string, Factory<AbstractProductT>*>::Iterator Factory<AbstractProductT>::end() 
	{
		return sFactoryMap.end();
	}

	template <typename AbstractProductT>
	void Factory<AbstractProductT>::Add(Factory& factory)
	{
		if (!sFactoryMap.ContainsKey(factory.ClassName())) //add only if not already present
		{
			sFactoryMap.Insert(factory.ClassName(), &factory);
		}
	}

	template <typename AbstractProductT>
	void Factory<AbstractProductT>::Remove(const Factory& factory)
	{
		sFactoryMap.Remove(factory.ClassName());
	}

	template <typename AbstractProductT>
	bool Factory<AbstractProductT>::ContainsFactory(const std::string& name)
	{
		return sFactoryMap.ContainsKey(name);
	}

	template <typename AbstractProductT>
	std::uint32_t Factory<AbstractProductT>::FactoryCount()
	{
		return sFactoryMap.Size();
	}
}