/**	@file IXmlParseHelper.h
*	@brief declaration for IXmlParseHelper
*/

#pragma once
#include "XmlParseMaster.h"
#include "hashmap.h"
#include <cstring>

namespace Library
{
	/**	@class IXmlParseHelper
	*	@brief Interface / abstract class for parse helpers
	*/
	class IXmlParseHelper
	{	
	public:
		typedef XmlParseMaster::SharedData SharedData;

		/** @brief constructor to intialise the instance */
		IXmlParseHelper() = default;
		
		/** @brief destructor to free memory */
		virtual ~IXmlParseHelper() = default;
		
		/**	@brief Method to default or reset local data in the helper */
		virtual void Initialize();

		/**	@brief Method to handle start tags and their attributes
		*	@param pointer to the shared data
		*	@param name of the tag being handled
		*	@param list of attributes from the tag
		*	@return true if the data was handled by this helper, false otherwise
		*/
		virtual bool StartElementHandler(SharedData* sharedData, const std::string& tagName, const HashMap<std::string, std::string>& attributes);

		/**	@brief Method to handle end tags
		*	@param pointer to the shared data
		*	@param name of the tag being handled
		*	@return true if the data was handled by this helper, false otherwise
		*/
		virtual bool EndElementHandler(SharedData* sharedData, const std::string& tagName);

		/**	@brief Method to handle inner text between start and end tags
		*	@param pointer to the shared data
		*	@param value of the inner text
		*	@return true if the data was handled by this helper, false otherwise
		*/
		virtual bool CharDataHandler(SharedData* sharedData, const std::string& innerText);

		/** Method to create copies of this helper */
		virtual IXmlParseHelper* Create() const = 0;

		/**	@brief Method to check if the two helpers are the same
		*	@param the helper being compared
		*	@return true if they are the same type, false otherwise
		*/
		virtual bool operator==(const IXmlParseHelper& rhs) const;

		/**	@brief Method to check if the two helpers are not the same
		*	@param the helper being compared
		*	@return true if they are not the same type, false otherwise
		*/
		virtual bool operator!=(const IXmlParseHelper& rhs) const;

		/**	@brief Marked delete to disallow. Use Clone() to obtain a new copy */
		IXmlParseHelper(const IXmlParseHelper& rhs) = delete;

		/**	@brief Marked delete to disallow. Use Clone() to obtain a new copy */
		IXmlParseHelper& operator=(const IXmlParseHelper& rhs) = delete;
	};
}