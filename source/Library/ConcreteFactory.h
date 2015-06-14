#pragma once
#include "Factory.h"

namespace Library
{

#define CONCRETE_FACTORY(ConcreteProductType, AbstractProductType)						\
	class ConcreteProductType ## Factory final : public Factory<AbstractProductType>	\
	{																					\
	public:																				\
		ConcreteProductType ## Factory() :mClassName(#ConcreteProductType)				\
		{																				\
			Add(*this);																	\
		}																				\
																						\
		virtual ~ConcreteProductType ## Factory()										\
		{																				\
			Remove(*this);																\
		}																				\
																						\
		virtual const std::string& ClassName() const override							\
		{																				\
			return mClassName;															\
		}																				\
	private:																			\
		virtual AbstractProductType* Create() const override							\
		{																				\
			return new ConcreteProductType();											\
		}																				\
																						\
		std::string mClassName;															\
	};																					
}