/**	@file XmlParseHelperAction.cpp
*	@brief Definitions of XmlParseHelperAction
*/

#include "pch.h"
#include "XmlParseHelperAction.h"

namespace Library
{
#pragma region Constants
	 const std::string XmlParseHelperAction::ActionIfElementName="if";
	 const std::string XmlParseHelperAction::IfConditionClauseName="condition";
	 const std::string XmlParseHelperAction::IfThenClauseName="then";
	 const std::string XmlParseHelperAction::IfElseClauseName="else";
	 const std::string XmlParseHelperAction::ActionListElementName = "actions";
	 const std::string XmlParseHelperAction::IncrementElementName = "increment";
	 const std::string XmlParseHelperAction::DecrementElementName = "decrement";
	 const std::string XmlParseHelperAction::ReactionElementName = "reaction";
	 const std::string XmlParseHelperAction::ActionElementName = "action";

	 const std::string XmlParseHelperAction::NameAttribute="name";
	 const std::string XmlParseHelperAction::ValueAttribute="value";
	 const std::string XmlParseHelperAction::ClassAttribute = "class";

	 const std::string XmlParseHelperAction::ActionIfClassName = "ActionIf";
	 const std::string XmlParseHelperAction::ActionListClassName = "ActionList";
	 const std::string XmlParseHelperAction::IncrementClassName = "IncrementAction";
	 const std::string XmlParseHelperAction::DecrementClassName = "DecrementAction";
	 const std::string XmlParseHelperAction::ActionClassName = "ActionEvent";
	 const std::string XmlParseHelperAction::ReactionClassName = "ReactionAttributed";

#pragma endregion

	 void XmlParseHelperAction::Initialize()
	 {
		 IXmlParseHelper::Initialize();

		 if (!mAttributesStack.IsEmpty())
		 {
			 mAttributesStack.Clear();
		 }
	 }

	 bool XmlParseHelperAction::StartElementHandler(SharedData* sharedData, const std::string& tagName, const HashMap<std::string, std::string>& attributes)
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

		 Scope* currentScope = tableData->GetParsedScope();
		 if (currentScope == nullptr)
		 {
			 return false;
		 }

		 //check if tag is supported by helper
		 if (!IsTagSupported(tagName))
		 {
			 return false;
		 }

		 //check if name attribute is present
		 if (!attributes.ContainsKey(NameAttribute))
		 {
			 throw std::exception("Name attribute is required");
		 }

		 const std::string& name = attributes.At(NameAttribute);

		 if (tableData->mContextStack.IsEmpty())
		 {
			 throw std::exception("Actions need to be nested under world, entity, sector or other actions");
		 }
		 const std::string& parentTag = tableData->mContextStack.Top();

		 Action* newAction=nullptr;

		 //handle action tags
		 if (tagName == ActionIfElementName)
		 {
			 if (parentTag != XmlParseHelperTable::WorldElementName && parentTag != XmlParseHelperTable::SectorElementName && 
				 parentTag != XmlParseHelperTable::EntityElementName && !IsTagSupported(parentTag))
			 {
				 throw std::exception("If needs to be nested under world, entity, sector or other actions");
			 }

			 newAction = CreateAction(currentScope, ActionIfClassName, name);
		 }
		 else if (tagName == IfThenClauseName || tagName == IfElseClauseName)
		 {
			 if (parentTag != ActionIfElementName)
			 {
				 throw std::exception("Clause of If nested under other elements");
			 }

			 newAction = new ActionList(name);

			 //using CreateAction adopts it into SubActions(), we want it in the prescribed attribute; hence adopting it the regular way
			 if (tagName == IfThenClauseName)
			 {
				 currentScope->As<ActionIf>()->ThenClause()->Adopt(*newAction, name);
			 }
			 else
			 {
				 currentScope->As<ActionIf>()->ElseClause()->Adopt(*newAction, name);
			 }
		 }
		 else if (tagName == ActionListElementName)
		 {
			 newAction = CreateAction(currentScope, ActionListClassName, name);
		 }
		 else if (tagName == IncrementElementName)
		 {
			 newAction = CreateAction(currentScope, IncrementClassName, name);
		 }
		 else if (tagName == DecrementElementName)
		 {
			 newAction = CreateAction(currentScope, DecrementClassName, name);
		 }
		 else if (tagName == ReactionElementName)
		 {
			 newAction = CreateAction(currentScope, ReactionClassName, name);
		 }
		 else if (tagName == ActionElementName)
		 {
			 newAction = CreateAction(currentScope, ActionClassName, name);
		 }

		 //setting context to the newly created action
		 tableData->SetCurrentScope(newAction);

		 //pushing onto stack even if it is empty
		 mAttributesStack.Push(attributes);

		 //updating state
		 tableData->mContextStack.Push(tagName);

		 return true;
	 }

	 bool XmlParseHelperAction::EndElementHandler(SharedData* sharedData, const std::string& tagName)
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

		 auto attributes = mAttributesStack.Pop(); //remove the attributes for the element

		 //handle tags
		 const std::string& parentTag = tableData->mContextStack.Top();

		 Action* currentAction = currentScope->As<Action>();

		 if (currentAction != nullptr)
		 {
			 if (parentTag == XmlParseHelperTable::WorldElementName)
			 {
				 tableData->SetCurrentScope(currentAction->GetWorld());
			 }
			 else if (parentTag == XmlParseHelperTable::SectorElementName)
			 {
				 tableData->SetCurrentScope(currentAction->GetSector());
			 } 
			 else if (parentTag == XmlParseHelperTable::EntityElementName)
			 {
				 tableData->SetCurrentScope(currentAction->GetEntity());
			 }
			 else //it is nested in an action
			 {
				 if (tagName == IfThenClauseName || tagName == IfElseClauseName)
				 {
					 //set scope back to the holding action scope
					 //1st GetParent to get the scope that is identified by name "then" or "else"
					 //2nd gets the action
					 tableData->SetCurrentScope(currentAction->GetParent()->GetParent());
				 }
				 else
				 {
					 tableData->SetCurrentScope(currentAction->GetAction());
				 }
			 }
		 }

		 return true;
	 }

	 IXmlParseHelper* XmlParseHelperAction::Create() const
	 {
		 XmlParseHelperAction* newHelper = new XmlParseHelperAction();
		 return newHelper;
	 }

	 bool XmlParseHelperAction::IsTagSupported(const std::string& tagName) const
	 {
		 if (tagName != ActionIfElementName && tagName != IfThenClauseName && tagName!= IfElseClauseName
			 && tagName != ActionListElementName && tagName != IncrementElementName && tagName != DecrementElementName 
			 && tagName != ReactionElementName && tagName != ActionElementName)
		 {
			 return false;
		 }

		 return true;
	 }

	 //helper for having all the different CreateAction methods in one place
	 Action* XmlParseHelperAction::CreateAction(Scope* currentScope,const std::string& className, const std::string& instanceName) const
	 {
		 if (!Factory<Action>::ContainsFactory(className))
		 {
			 throw std::exception("Factory for action not found");
		 }

		 Action* newAction=nullptr;
		 
		 assert(currentScope != nullptr);

		 if (currentScope->Is("World"))
		 {
			 newAction = currentScope->As<World>()->CreateAction(className, instanceName);
		 }
		 else if (currentScope->Is("Sector"))
		 {
			 newAction = currentScope->As<Sector>()->CreateAction(className, instanceName);
		 }
		 else if (currentScope->Is("Entity"))
		 {
			 newAction = currentScope->As<Entity>()->CreateAction(className, instanceName);
		 }
		 else if (currentScope->Is("Action"))
		 {
			 newAction = currentScope->As<Action>()->CreateSubAction(className, instanceName);
		 }
		 else
		 {
			 throw std::exception("Action nested under invalid tag");
		 }

		 return newAction;
	 }
}