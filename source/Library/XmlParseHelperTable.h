/**	@file XmlParseHelperTable.h
*	@brief Declaration of XmlParseHelperTable
*/

#pragma once
#include "hashmap.h"
#include "stack.h"

/** Supported grammar : (grammar is case sensitive)
*	World:
*		Tag name : world
*		Attributes supported : name (required)
*		Nesting of worlds : not allowed
*	There should be only world. If parsing a world, pass in a world through the shared data.
*	If the root is a world element, we take it that the root corresponds to the world passed in. The name of the world will be 
*	For clarity, it is recommended to have the root as a world tag, when parsing worlds.
*	Adding scopes and datums under world directly results in adding them as auxillary attributes to that world.
*
*	Sector:
*		Tag name : sector
*		Attributes supported : name (required)
*		Nesting of sectors : not allowed
*	Creates a sector named with the value in the name attribute and adds it to the current world. 
*	Ensure that the sector factor is instantiated before parsing.
*	Sectors should be present under a world tag. It will work even if not but it is recommended for clarity. 
*	Adding scopes and datums under sector directly results in adding them as auxillary attributes to that sector.
*	
*	Entity:
*		Tag name : entity
*		Attributes supported : name (required), class (required)
*		Nesting of entities : not allowed
*	Creates an entity of specified class and names it with the name attribute value.
*	Ensure that the class's factory is instantiated before parsing.
*	Sector should only be present under a world tag. It will work even if not but it is recommended for clarity. 
*	Adding scopes and datums under sector directly results in adding them as auxillary attributes to that sector.

*	Scope:
*		Tag name : table
*		Attributes supported : name (required for non-root tables)
*		Nesting of scopes : supported
*	If the root element is not a table element, the element is added to the scope passed it. If the root is a table element,
*	we take it that the root corresponds to the scope passed in. If a name is provided for the root, it will not be stored anywhere.
*	For clarity, it is recommended to have the root as a table tag, when not parsing worlds.
*	For nested scopes, nest table elements inside each other. For array of nested scopes, nest table elements inside the same parent.
*	Scopes are added in the order they are parsed. No support for indexing available
*	If parsing a scope, pass in scope to the shared data.
*
*	Integer, Float, String, Vector and Matrix:
*		Tag names : integer, float, string, vector, matrix respectively
*		Attributes supported :  name (required), value, size, index
*		Inner text : supported
*		Nesting of the above elements : not supported
*		Array delimiter : ;
*	Either value or inner text between tags can be used to provide values for the element. If both are present,  preference is given to the value attribute.
*	If no value is present, the default value is set.
*
*	Size attribute -> size of the array
*	Index -> position to add the element at
*
*	Below dictates the behaviour of the tags when present together
*	Size	Index	Parse result
*	yes		yes		size is set to maximum of size or index+1. The first value if parsed and set at the index. Extra data is ignored
*	yes		no		"size" number of elements are parsed and appended to the back of the array. Extra data is ignored
*	no		yes		size is set to index+1. The first value is parsed and set at the index. Extra data is ignored
*	no		no		all the data provided are parsed and appended to the back if the array.
*/

namespace Library
{
	/**	@class XmlParseHelperTable
	*	@brief Helper to parse for table data
	*/
	class XmlParseHelperTable final : public IXmlParseHelper 
	{
	public:
		/**	Default constructor to initialise */
		XmlParseHelperTable()=default;

		/**	Default destructor to release held data */
		virtual ~XmlParseHelperTable()=default;

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

		/**	@brief Handler for inner text between tags
		*	@param inner text, or a part of it
		*	@return true, if the data was handles by this helper, false, if the helper doesnt support the data or cant process it
		*/
		virtual bool CharDataHandler(SharedData* sharedData, const std::string& innerText) override;
		
		/**	@brief Create a new instance
		*	@return a new instance of this class, data is not copied.
		*/
		virtual IXmlParseHelper* Create() const override;

		//Tags and attributes supported by the helper
		static const std::string ScopeElementName;
		static const std::string EntityElementName;
		static const std::string SectorElementName;
		static const std::string WorldElementName;

		static const std::string IntegerElementName;
		static const std::string FloatElementName;
		static const std::string VectorElementName;
		static const std::string MatrixElementName;
		static const std::string StringElementName;

		static const std::string NameAttribute;
		static const std::string ValueAttribute;
		static const std::string SizeAttribute;
		static const std::string IndexAttribute;
		static const std::string ClassAttribute;
		static const char ValueDelimiter;

	private:
		Stack<HashMap<std::string, std::string>> mAttributesStack; ///< stack where the attributes from each tag are stored.
		bool mValueAttributePresent = false; ///< if the value attribute was present in the attribute list

		bool IsTagSupported(const std::string& tagName) const;
	};
}
