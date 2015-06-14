/**	@file XmlParseHelperTable.cpp
*	@brief Implementation of XmlParseHelperTable
*/

#include "pch.h"
#include "XmlParseHelperTable.h"
#include "TableSharedData.h"

namespace Library
{
#pragma region Constants
	const std::string XmlParseHelperTable::ScopeElementName = "table";
	const std::string XmlParseHelperTable::EntityElementName = "entity";
	const std::string XmlParseHelperTable::SectorElementName = "sector";
	const std::string XmlParseHelperTable::WorldElementName = "world";

	const std::string XmlParseHelperTable::IntegerElementName = "integer";
	const std::string XmlParseHelperTable::FloatElementName = "float";
	const std::string XmlParseHelperTable::VectorElementName = "vector";
	const std::string XmlParseHelperTable::MatrixElementName = "matrix";
	const std::string XmlParseHelperTable::StringElementName = "string";

	const std::string XmlParseHelperTable::NameAttribute = "name";
	const std::string XmlParseHelperTable::ValueAttribute = "value";
	const std::string XmlParseHelperTable::SizeAttribute = "size";
	const std::string XmlParseHelperTable::IndexAttribute = "index";
	const std::string XmlParseHelperTable::ClassAttribute = "class";


	const char XmlParseHelperTable::ValueDelimiter = ';';
#pragma endregion

	void XmlParseHelperTable::Initialize()
	{
		IXmlParseHelper::Initialize();

		if (!mAttributesStack.IsEmpty())
		{
			mAttributesStack.Clear();
			mValueAttributePresent = false;
		}
	}

	bool XmlParseHelperTable::StartElementHandler(SharedData* sharedData, const std::string& tagName, const HashMap<std::string, std::string>& attributes)
	{
		if (sharedData == nullptr)
		{
			return false;
		}

		TableSharedData* tableData = sharedData->As<TableSharedData>();
		if (tableData == nullptr)
		{
			return false;
		}

		if (tableData->GetParsedScope() == nullptr)
		{
			return false;
		}

		//check if tag is supported by helper
		if (!IsTagSupported(tagName))
		{
			return false;
		}

		//check nesting for non scope tags
		if (!tableData->mContextStack.IsEmpty())
		{
			const std::string& parentTag = tableData->mContextStack.Top();

			if (parentTag!= ScopeElementName &&  parentTag!=EntityElementName && parentTag!= SectorElementName
				&& parentTag != WorldElementName && parentTag != XmlParseHelperAction::ActionIfElementName 
				&& parentTag != XmlParseHelperAction::ActionElementName && parentTag != XmlParseHelperAction::ReactionElementName)
			{
				std::string temp = "Cant have nested elements under " + parentTag;
				throw std::exception(temp.c_str());
			}
		}

		//check if name attribute is present
		if (!attributes.ContainsKey(NameAttribute))
		{
			throw std::exception("Name attribute is required");
		}

		//depth checking to ensure that the root corresponds to the parsed scope
		//ignoring the table element at depth 1 as it is the root
		if (tagName == ScopeElementName && tableData->Depth()!=1)
		{
			const std::string& scopeName = attributes.At(NameAttribute);

			Scope* newScope = tableData->GetParsedScope()->AppendScope(scopeName);
			tableData->SetCurrentScope(newScope); //move down the hierarchy
		}
		else if (tagName == WorldElementName)
		{
			if (tableData->Depth() != 1)
			{
				throw std::exception("World tag needs to be the root");
			}

			World* world = tableData->GetParsedScope()->As<World>();

			//update the name of the world to be the one from the xml
			if (world != nullptr)
			{
				world->SetName(attributes.At(NameAttribute));
			}
			else
			{
				throw std::exception("Passed in scope must be a world");
			}
		}
		else if (tagName == SectorElementName)
		{
			World* world = tableData->GetParsedScope()->As<World>();
			if (world != nullptr)
			{
				const std::string& sectorName = attributes.At(NameAttribute);
				Sector* newSector = world->CreateSector(sectorName);

				if (newSector == nullptr)
				{
					throw std::exception("Factory for sector not present");
				}

				tableData->SetCurrentScope(newSector);
			}
			else
			{
				throw std::exception("Sectors must be nested inside world");
			}
		}
		else if (tagName == EntityElementName)
		{
			//check if class name attribute is present. class is required
			if (!attributes.ContainsKey(ClassAttribute))
			{
				throw std::exception("Class attribute is required for entity");
			}

			Sector* sector = tableData->GetParsedScope()->As<Sector>();
			if (sector != nullptr)
			{
				const std::string& entityName = attributes.At(NameAttribute);
				const std::string& className = attributes.At(ClassAttribute);

				Entity* newEntity=sector->CreateEntity(className, entityName);
				
				if (newEntity == nullptr)
				{
					throw std::exception("Factory for entity not present");
				}
				
				tableData->SetCurrentScope(newEntity);
			}
			else
			{
				throw std::exception("Entity must be nested inside sector");
			}
		}
		else
		{
			//marking if the value attribute was encountered or not, for checking in char data handler
			if (attributes.ContainsKey(ValueAttribute))
			{
				mValueAttributePresent = true;
			}
			else
			{
				mValueAttributePresent = false;
			}
		}

		//pushing onto stack even if it is empty
		mAttributesStack.Push(attributes);

		//updating state
		tableData->mContextStack.Push(tagName);

		return true;
	}

	bool XmlParseHelperTable::CharDataHandler(SharedData* sharedData, const std::string& innerText)
	{
		if (sharedData == nullptr)
		{
			return false;
		}

		TableSharedData* tableData = sharedData->As<TableSharedData>();
		if (tableData == nullptr)
		{
			return false;
		}

		std::string tagName = tableData->mContextStack.Top();

		//not allowing inner text parsing for table or other elements
		if (tagName != IntegerElementName && tagName != FloatElementName && tagName != StringElementName && tagName != VectorElementName && tagName != MatrixElementName)
		{
			return false;
		}

		//add inner text as a value attribute, only if it wasnt encountered
		if (!mValueAttributePresent)
		{
			if (mAttributesStack.IsEmpty())
			{
				throw std::exception("Attributes stack is empty");
			}

			auto& attributesStackTop = mAttributesStack.Top();

			//if already one was added, append to it (in case the inner text spans several lines)
			//else add a newe one
			if (attributesStackTop.ContainsKey(ValueAttribute))
			{
				attributesStackTop[ValueAttribute].append(innerText);
			}
			else
			{
				attributesStackTop.Insert(ValueAttribute, innerText);
			}
		}

		return true;
	}

	bool XmlParseHelperTable::EndElementHandler(SharedData* sharedData, const std::string& tagName)
	{
		if (sharedData == nullptr)
		{
			return false;
		}

		TableSharedData* tableData = sharedData->As<TableSharedData>();
		if (tableData == nullptr)
		{
			return false;
		}

		//checking for supported tags
		if (!IsTagSupported(tagName))
		{
			return false;
		}
		
		//state checking
		if (tableData->mContextStack.IsEmpty() || tableData->mContextStack.Top() != tagName)
		{
			throw std::exception("XML processing error");
		}
		tableData->mContextStack.Pop();
	
		Scope* currentScope = tableData->GetParsedScope();
		if (currentScope == nullptr)
		{
			throw std::exception("Current Scope is null");
		}
		
		auto attributes = mAttributesStack.Pop();//remove the attributes for the element

		if (tagName == ScopeElementName)
		{
			//move up the hierarchy
			Scope* previousScope = currentScope->GetParent();
			tableData->SetCurrentScope(previousScope);
		}
		else if (tagName == SectorElementName)
		{
			//move up the hierarchy to world
			Sector* currentSector = currentScope->As<Sector>();

			if (currentSector != nullptr)
			{
				tableData->SetCurrentScope(currentSector->GetWorld());
			}
		}
		else if (tagName == EntityElementName)
		{
			//move up the hierarchy to sector
			Entity* currentEntity = currentScope->As<Entity>();

			if (currentEntity != nullptr)
			{
				tableData->SetCurrentScope(currentEntity->GetSector());
			}
		}
		else if (tagName != WorldElementName) //for all elements except world
		{
			auto& datum = currentScope->Append(attributes[NameAttribute]);

			if (datum.IsExternal())
			{
				throw std::exception("Datum is external");
			}

			//find the type corresponding to the tag
			Datum::DatumType type = Datum::DatumType::Unknown;
			if (tagName == IntegerElementName)
			{
				type = Datum::DatumType::Integer;
			}
			else if (tagName == FloatElementName)
			{
				type = Datum::DatumType::Float;
			}
			else if (tagName == StringElementName)
			{
				type = Datum::DatumType::String;
			}
			else if (tagName == VectorElementName)
			{
				type = Datum::DatumType::Vector;
			}
			else if (tagName == MatrixElementName)
			{
				type = Datum::DatumType::Matrix;
			}

			//if it is a new datum, set its type
			if (datum.GetType() == Datum::DatumType::Unknown)
			{
				datum.SetType(type);
			}
			//throw exception if trying to append a different type
			else if (datum.GetType() != type)
			{
				throw std::exception("Type mismatch");
			}
			
			std::string value = "";
			if (attributes.ContainsKey(ValueAttribute))
			{
				value = attributes[ValueAttribute];
			}

			std::stringstream sstream(value);
			std::string extractedValue;

			bool containsSize = attributes.ContainsKey(SizeAttribute);
			bool containsIndex = attributes.ContainsKey(IndexAttribute);

			if (containsSize && containsIndex)
			{
				int size = std::stoi(attributes[SizeAttribute]);
				int index = std::stoi(attributes[IndexAttribute]);

				//find maximum of size and index+1
				if (size > index + 1)
				{
					datum.SetSize(size);
				}
				else
				{
					datum.SetSize(index + 1);
				}
				
				std::getline(sstream, extractedValue, ValueDelimiter); //fool proof against user putting in multiple values
				datum.TrySetFromString(extractedValue, index);
			}

			else if (containsIndex && !containsSize)
			{
				int index = std::stoi(attributes[IndexAttribute]);

				std::getline(sstream, extractedValue, ValueDelimiter);
				datum.TrySetFromString(extractedValue, index);
			}

			else if (containsSize && !containsIndex)
			{
				int existingElementsCount = datum.Size();

				int size=std::stoi(attributes[SizeAttribute])+existingElementsCount;
				int elementCount=existingElementsCount;

				while (std::getline(sstream, extractedValue, ValueDelimiter))
				{
					datum.TrySetFromString(extractedValue,elementCount++);

					//prevent user from reading more than necessary
					if (elementCount >= size)
					{
						break;
					}
				}

				//default the rest, if not enough data
				while(elementCount < size)
				{
					datum.TrySetFromString("", elementCount++);
				}
			}

			else
			{
				int elementCount = datum.Size();

				while (std::getline(sstream, extractedValue, ValueDelimiter))
				{
					datum.TrySetFromString(extractedValue, elementCount++);
				}
			}
		}
		
		return true;
	}

	IXmlParseHelper* XmlParseHelperTable::Create() const
	{
		XmlParseHelperTable* newHelper = new XmlParseHelperTable();
		return newHelper;
	}

	bool XmlParseHelperTable::IsTagSupported(const std::string& tagName) const
	{
		if (tagName != ScopeElementName && tagName != IntegerElementName && tagName != FloatElementName
			&& tagName != StringElementName && tagName != VectorElementName && tagName != MatrixElementName
			&& tagName != EntityElementName && tagName != SectorElementName && tagName != WorldElementName)
		{
			return false;
		}

		return true;
	}
}
