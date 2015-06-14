/**	@file XmlParseHelperAction.h
*	@brief Declarations of XmlParseHelperAction
*/

#pragma once

namespace Library
{
	class Action;

	/**	@class XmlParseHelperAction
	*	@brief Parse helper that parses action related tags
	*/
	class XmlParseHelperAction final : public IXmlParseHelper
	{
	public:
		/**	@brief Default constructor */
		XmlParseHelperAction() = default;

		/**	@brief Default destructor */
		virtual ~XmlParseHelperAction()=default;

		/**	@brief Reset the members to their initial state */
		virtual void Initialize() override;

		/**	@brief Handler for start tags of the xml
		*	@param shared data being populated by the system
		*	@param name of the tag being handled
		*	@param attributes in the tag
		*	@return true, if the data was handles by this helper, false, if the helper doesnt support the data or cant process it
		*/
		virtual bool StartElementHandler(SharedData* sharedData, const std::string& tagName, const HashMap<std::string, std::string>& attributes) override;
		
		/**	@brief Handler for end tags of the xml
		*	@param shared data being populated by the system
		*	@param name of the tag being handled
		*	@return true, if the data was handles by this helper, false, if the helper doesnt support the data or cant process it
		*/
		virtual bool EndElementHandler(SharedData* sharedData, const std::string& tagName) override;
		
		/**	@brief Create a new instance
		*	@return a new instance of this class, data is not copied.
		*/
		virtual IXmlParseHelper* Create() const override;

		//constants for supported grammar
		static const std::string ActionIfElementName;
		static const std::string IfConditionClauseName;
		static const std::string IfThenClauseName;
		static const std::string IfElseClauseName;
		static const std::string ActionListElementName;
		static const std::string IncrementElementName;
		static const std::string DecrementElementName;
		static const std::string ReactionElementName;
		static const std::string ActionElementName;

		static const std::string NameAttribute;
		static const std::string ValueAttribute;
		static const std::string ClassAttribute;

		static const std::string ActionIfClassName;
		static const std::string ActionListClassName;
		static const std::string IncrementClassName;
		static const std::string DecrementClassName;
		static const std::string ActionClassName;
		static const std::string ReactionClassName;

	private:
		Stack<HashMap<std::string, std::string>> mAttributesStack;

		/**	@brief Helper to check if the tag is supported
		*	@param tag currently processing
		*	@return true if the helper can handle the tag, false otherwise
		*/
		bool IsTagSupported(const std::string& tagName) const;

		/**	@brief Helper to call create action based on the current scope
		*	@param current scope
		*	@param factory name of the action
		*	@param name of the action
		*	@return the new action
		*/
		Action* CreateAction(Scope* currentScope, const std::string& className, const std::string& instanceName) const;
	};

}