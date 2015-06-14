/**	@file Attributed.cpp
*	@brief Implementation of Attributed
*/

#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(Attributed)

	// Initialise the hashmap
	//HashMap<std::uint32_t, Vector<Attributed::Signature>> Attributed::sSignatures = HashMap<std::uint32_t, Vector<Attributed::Signature>>();

	Attributed::Attributed()
		: mSignatures()
	{
		//add the this attribute
		Append("this")=(RTTI*)this;
	}

	Attributed::Attributed(const Attributed& rhs) :
		Scope(rhs)
	{
		*this = rhs;
		//(*this)["this"] = (RTTI*)this;
	}

	Attributed& Attributed::operator=(const Attributed& rhs)
	{
		if (*this != rhs)
		{
			Scope::operator=(rhs);
			Append("this") = (RTTI*)this;
		}

		return *this;
	}

	void Attributed::Populate()
	{
		/*auto& temp = sSignatures[TypeIdInstance()];
		std::uint32_t size = temp.Size();*/
		
		std::uint32_t size = mSignatures.Size();

		for (std::uint32_t i = 0; i < size; ++i)
		{
			Signature& signature = GetSignature(i);
			if (signature.Type == Datum::DatumType::Table)
			{
				Scope* scope = AppendScope(signature.Name);
				scope = (Scope*)signature.InitialValue;
			}
			else
			{
				Datum& datum = Append(signature.Name);

				if (signature.Storage == nullptr)
				{
					//internal storage
					datum.SetType(signature.Type);
					//reserve
					datum.SetSize(signature.DataSize);
					
					//deep copy 
					switch (signature.Type)
					{
					case Datum::DatumType::Float:
						for (std::uint32_t i = 0; i < signature.DataSize; i++)
						{
							if (signature.InitialValue==nullptr)
							{
								datum.Set(0.0f, i);
							}
							else
							{
								datum.Set(((float*)signature.InitialValue)[i], i);
							}
						}
						break;

					case Datum::DatumType::Integer:
						for (std::uint32_t i = 0; i < signature.DataSize; i++)
						{
							if (signature.InitialValue==nullptr)
							{
								datum.Set(0, i);
							}
							else
							{
								datum.Set(((std::int32_t*)signature.InitialValue)[i], i);
							}
						}
						break;

					case Datum::DatumType::Matrix:
						for (std::uint32_t i = 0; i < signature.DataSize; i++)
						{
							if (signature.InitialValue == nullptr)
							{
								datum.Set(glm::mat4(0), i);
							}
							else
							{
								datum.Set(((glm::mat4*)signature.InitialValue)[i], i);
							}
						}
						break;

					case Datum::DatumType::Pointer:
						for (std::uint32_t i = 0; i < signature.DataSize; i++)
						{
							if (signature.InitialValue == nullptr)
							{
								throw std::exception("Value is null");
							}
							else
							{
								datum.Set(&((RTTI*)signature.InitialValue)[i], i);
							}
						}
						break;

					case Datum::DatumType::String:
						for (std::uint32_t i = 0; i < signature.DataSize; i++)
						{
							if (signature.InitialValue == nullptr)
							{
								datum.Set("", i);
							}
							else
							{
								datum.Set(((std::string*)signature.InitialValue)[i], i);
							}
						}
						break;

					case Datum::DatumType::Vector:
						for (std::uint32_t i = 0; i < signature.DataSize; i++)
						{
							if (signature.InitialValue == nullptr)
							{
								datum.Set(glm::vec4(0), i);
							}
							else
							{
								datum.Set(((glm::vec4*)signature.InitialValue)[i], i);
							}
						}
						break;

					case Datum::DatumType::Table:
						for (std::uint32_t i = 0; i < signature.DataSize; i++)
						{
							if (signature.InitialValue == nullptr)
							{
								datum.Set(new Scope(), i);
							}
							else
							{
								datum.Set(&((Scope*)signature.InitialValue)[i], i);
							}
							//adopt???
						}
						break;

					default:
						throw std::exception("Invalid datum type");
						break;
					}
				}
				else
				{
					//external
					switch (signature.Type)
					{
					case Datum::DatumType::Float:
						datum.SetStorage((float*)signature.Storage,signature.DataSize);
						break;

					case Datum::DatumType::Integer:
						datum.SetStorage((std::int32_t*)signature.Storage, signature.DataSize);
						break;

					case Datum::DatumType::Matrix:
						datum.SetStorage((glm::mat4*)signature.Storage, signature.DataSize);
						break;

					case Datum::DatumType::Pointer:
					{
						RTTI* ptrCopy = static_cast<RTTI*>(signature.Storage);
						datum.SetStorage(&ptrCopy, signature.DataSize);
					}
						break;

					case Datum::DatumType::String:
						datum.SetStorage((std::string*)signature.Storage, signature.DataSize);
						break;

					case Datum::DatumType::Vector:
						datum.SetStorage((glm::vec4*)signature.Storage, signature.DataSize);
						break;

					case Datum::DatumType::Table:
					{
						Scope* ptrCopy = static_cast<Scope*>(signature.Storage);
						datum.SetStorage(&ptrCopy, signature.DataSize);
					}
						break;

					default:
						throw std::exception("Invalid datum type");
						break;
					}
				}
			}
		}
	}

	bool Attributed::IsPrescribedAttribute(const std::string& attributeName) const
	{
		//TODO check if isattribute is true

		/*for (auto& value : sSignatures[TypeIdInstance()])
		{
			if (value.Name == attributeName)
			{
				return true;
			}
		}*/

		for (std::uint32_t i = 1; i < AuxiliaryBegin();i++) //ignoring this
		{
			if (mOrderList[i]->first == attributeName)
			{
				return true;
			}
		}

		return false;
	}

	bool Attributed::IsAuxiliaryAttribute(const std::string& attributeName) const
	{
		return (IsAttribute(attributeName) && !IsPrescribedAttribute(attributeName));
	}

	bool Attributed::IsAttribute(const std::string& attributeName) const
	{
		return (Find(attributeName)!=nullptr);
	}

	Datum& Attributed::AppendAuxiliaryAttribute(const std::string& attributeName)
	{
		if (IsPrescribedAttribute(attributeName))
		{
			throw std::exception("Attribute is a prescribed attribute");
		}

		if (attributeName == "this")
		{
			throw std::exception("Cant modify 'this' attribute");
		}

		return Append(attributeName);
	}

	std::uint32_t Attributed::AuxiliaryBegin() const
	{
		return mSignatures.Size() + 1;

		//return sSignatures[TypeIdInstance()].Size() + 1; // + 1 for this attribute
	}

	Attributed::Signature& Attributed::GetSignature(std::uint32_t index)
	{
		//return (sSignatures[TypeIdInstance()])[index];
		return mSignatures[index];
	}

	Attributed::Signature::Signature(const std::string& name, Datum::DatumType type, void* initialValue, std::uint32_t size, void* storage) :
		Name(name), Type(type), InitialValue(initialValue), DataSize(size), Storage(storage)
	{
	}

	Attributed::Signature::Signature() :
		Signature(std::string(), Datum::DatumType::Unknown, nullptr, 0, nullptr)
	{
	}

	bool Attributed::operator==(const Attributed& rhs) const
	{
		return Scope::operator==(rhs);
	}

	bool Attributed::operator!=(const Attributed& rhs) const
	{
		return Scope::operator!=(rhs);
	}

	void Attributed::Clear()
	{
		Scope::Clear();
		Append("this") = (RTTI*)this;
	}

	void Attributed::CopyAuxillaryAttributes(const Attributed& rhs)
	{
		for (std::uint32_t i = rhs.AuxiliaryBegin(); i < rhs.Size(); ++i)
		{
			InsertPair(rhs.GetPairAt(i)); //get the pair from rhs and add to this scope
		}
	}

}