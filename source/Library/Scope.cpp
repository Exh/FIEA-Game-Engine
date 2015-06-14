/**	@file Scope.cpp
*	@brief contains implementation of scope
*/
#include "pch.h"
#include "Scope.h"

namespace Library
{
	RTTI_DEFINITIONS(Scope)

	Scope::~Scope()
	{
		Orphan(); //doing this in clear
		Clear();
	}

	Scope::Scope(std::uint32_t initialCapacity):
		mTable(initialCapacity), mOrderList(initialCapacity),mParent(nullptr)
	{
	}

	void Scope::Clear()
	{
		//Orphan();

		for (auto& datumPair : mOrderList)
		{
			//do only if its a table and not external
			if (!(datumPair->second).IsExternal() && (datumPair->second).GetType() == Datum::DatumType::Table)
			{
				for (std::uint32_t i = 0; i < (datumPair->second).Size(); i++)
				{
					delete (datumPair->second).GetTable(i);
				}
			}
		}

		mOrderList.Clear();
		mTable.Clear();
	}

	Scope::Scope(const Scope& rhs)
		:Scope(rhs.Size())
	{
		*this = rhs;
	}

	Scope& Scope::operator=(const Scope& rhs)
	{
		if (this != &rhs)
		{
			//dont clear if the scope is empty but has memory allocated in the vector and hashmap
			if (Size() != 0)
			{
				Orphan();
				Clear();
			}

			for (auto& pair : rhs.mOrderList)
			{
				//deep copy the scopes for all cases, internal or external
				if (pair->second.GetType() == Datum::DatumType::Table)
				{
					for (std::uint32_t i = 0; i < pair->second.Size(); i++)
					{
						Scope* scope = AppendScope(pair->first);
						*scope = *(pair->second.GetTable(i));
					}
				}
				else
				{
					//let datum deep copy the rest
					Datum& datum = Append(pair->first);
					datum = pair->second;
				}
			}
		}
		return *this;
	}

	Datum* Scope::Find(const std::string& name) const
	{
		for (auto& value : mTable)
		{
			if (value.first == name)
			{
				return &(value.second);
			}
		}

		return nullptr;
	}

	Datum* Scope::Search(const std::string& name, Scope** foundScope) const
	{
		Datum* datum = nullptr;
		Scope* parent = const_cast<Scope*>(this);
		Scope* scope = nullptr;

		//keep looking recursively until the datum is found and until there is no more parents to search
		do
		{
			scope = parent;
			datum = scope->Find(name);
			parent = scope->mParent;

		} while (parent != nullptr && datum == nullptr);

		if (*foundScope != nullptr)
		{
			if (datum == nullptr)
			{
				*foundScope = nullptr;
			}
			else
			{
				*foundScope = scope;
			}
		}

		return datum;
	}

	Datum& Scope::Append(const std::string& name)
	{
		if (name == "")
		{
			throw std::exception("Invalid name");
		}

		bool wasInserted;

		auto it = mTable.Insert(name, Datum(), wasInserted);
		
		if (wasInserted)
		{
			mOrderList.PushBack(&(*it));
		}

		return (*it).second;
	}

	Scope* Scope::AppendScope(const std::string& name)
	{	
		return AppendScopeAt(name);
	}

	Scope* Scope::AppendScopeAt(const std::string& name, std::uint32_t index)
	{
		if (name == "")
		{
			throw std::exception("Invalid name");
		}

		Datum* datum = Find(name);
		if (datum != nullptr && (datum->GetType() != Datum::DatumType::Table || datum->IsExternal()))
		{
			throw std::exception("Invalid datum");
		}

		//create a new datum if not present
		if (datum == nullptr)
		{
			datum = &(Append(name));
		}

		Scope* newScope = new Scope();
		datum->SetType(Datum::DatumType::Table);
		Adopt(*newScope, name,index);

		return newScope;
	}

	void Scope::Adopt(Scope& child, const std::string& childName, std::uint32_t index)
	{		
		child.Orphan();

		auto it = mTable.Find(childName);

		if (it != mTable.end())
		{
			if ((*it).second.IsExternal())
			{
				throw std::exception("Datum is external");
			}

			//if found, insert the child 
			(*it).second.Insert(&child, index);
		}
		else
		{
			//create a new datum and add to it
			Datum& datum = Append(childName);
			datum.SetType(Datum::DatumType::Table);
			datum.Insert(&child, index);
		}

		child.mParent = this;

		//return child;
	}

	Scope* Scope::GetParent() const
	{
		return mParent;
	}

	Datum& Scope::operator[](const std::string& name)
	{
		return Append(name);
	}

	Datum& Scope::operator[](const std::uint32_t index)
	{
		if (index >= mOrderList.Size())
		{
			throw std::out_of_range("Accessing table out of bounds");
		}

		return (*mOrderList[index]).second;
	}

	bool Scope::operator==(const Scope& rhs) const
	{
		if (mOrderList.Size() != rhs.mOrderList.Size())
		{
			return false;
		}

		std::uint32_t i = 0;
		
		//added for attribute. 'this' is the first element of attribute. We dont want to compare since it will always be different
		if (mTable.ContainsKey("this"))
		{
			i = 1;
		}

		//de-reference and check the contents of the scopes in the order in which they were added
		for (; i < mOrderList.Size(); i++)
		{
			if (*(mOrderList[i]) != *(rhs.mOrderList[i]))
			{
				return false;
			}
		}

		return true;
	}

	bool Scope::operator!=(const Scope& rhs) const
	{
		return !(*this == rhs);
	}

	bool Scope::FindName(const Scope& data, std::string& foundName) const
	{
		//if (data == nullptr)
		//{
		//	throw std::exception("No data to find");
		//}

		//find the key of the datum the scope is in
		for (auto& pair : mTable)
		{
			if (pair.second.GetType() == Datum::DatumType::Table)
			{
				std::uint32_t index = pair.second.FindNestedScope(data);
				if (index < pair.second.Size())
				{
					foundName= pair.first;
					return true;
				}
			}
		}

		foundName = ""; //not string() since i m using that to check for empty string
		return false;
	}

	void Scope::Orphan()
	{
		if (mParent != nullptr)
		{
			for (auto& pair : mParent->mTable)
			{
				if (pair.second.GetType() == Datum::DatumType::Table)
				{
					if (pair.second.AbandonChild(*this))
					{
						mParent = nullptr;
						break;
					}
				}
			}
		}
	}

	bool Scope::CompareStructure(const Scope& rhs) const
	{
		//iterate through hashmap and check the datum type and size alone
		if (mTable.Size() != rhs.mTable.Size())
		{
			return false;
		}

		auto lhsIt = mTable.begin();
		auto rhsIt = rhs.mTable.begin();

		for (; lhsIt != mTable.end(), rhsIt != rhs.mTable.end();++lhsIt,++rhsIt)
		{
			if ((*lhsIt).first != (*rhsIt).first ||
				(*lhsIt).second.GetType() != (*rhsIt).second.GetType() ||
				(*lhsIt).second.Size() != (*rhsIt).second.Size())
			{
				return false;
			}
		}

		return true;
	}

	std::uint32_t Scope::Size() const
	{
		return mTable.Size();
	}

	Scope::Iterator Scope::begin()
	{
		return mOrderList.begin();
	}

	Scope::Iterator Scope::end()
	{
		return mOrderList.end();
	}

	Scope::PairType* Scope::GetPairAt(std::uint32_t index) const
	{
		return mOrderList[index];
	}

	void Scope::InsertPair(PairType* pair)
	{
		if (pair->second.GetType() == Datum::DatumType::Table)
		{		
			for (std::uint32_t i = 0; i < pair->second.Size(); ++i)
			{
				Scope* scope = AppendScope(pair->first);
				*scope = *(pair->second.GetTable(i));
			}
		}
		else
		{
			Datum& datum = Append(pair->first);
			datum = pair->second;
		}
	}
}