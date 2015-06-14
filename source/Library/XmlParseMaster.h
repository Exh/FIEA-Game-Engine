/**	@file XmlParseMaster.h
*	@brief Declarations of XmlParseMaster and SharedData classes
*/
#pragma once

#include "Slist.h"
#include "RTTI.h"
#include "expat.h"

namespace Library
{
	class IXmlParseHelper;

	/**	@class XmlParseMaster
	*	@brief The master parsing class that interfaces between Expat and the client
	*/
	class XmlParseMaster final
	{
	public:
		/**	@class SharedData
		*	@brief The data that will be passed around and populated throughout the parsing classes
		*/
		class SharedData : public RTTI
		{
			RTTI_DECLARATIONS(SharedData, RTTI)

		public:
			/**	@brief Constructor to initialise members to default */
			explicit SharedData(XmlParseMaster* parseMaster=nullptr);

			/**	@brief Pure virtual method that every inherited class must implement to dictate how a new copy of the data should be created.
			*	The data is generally default constructed
			*/
			virtual SharedData* Clone() const = 0;

			/**	@brief Setter for parse master 
			*	@param new value for parse master
			*/
			void SetXmlParseMaster(XmlParseMaster* parseMaster);

			/**	@brief Getter for parse master
			*	@return the address of the parse master
			*/
			XmlParseMaster* GetXmlParseMaster() const; 

			/**	@brief Method to increment the parsed depth. */
			void IncrementDepth();

			/**	@brief Method to decrement the parsed depth */
			void DecrementDepth();

			/**	@brief Get the current depth
			*	@return depth value
			*/
			std::uint32_t Depth() const;

			/**	@brief Marked delete to disallow. Use Clone() to obtain a new copy */
			SharedData(const SharedData& rhs) = delete;
			
			/**	@brief Marked delete to disallow. Use Clone() to obtain a new copy */
			SharedData& operator=(const SharedData& rhs) = delete;

			virtual void Initialise();
		private:
			XmlParseMaster* mXmlParseMaster;
			std::uint32_t mDepth;
		};

		/**	@brief Constructor to initialise members */
		explicit XmlParseMaster(SharedData* sharedData=nullptr, bool exceptionOnFail=false);

		/**	@brief Destructor to release all the resources. If the instance is a clone, destructor takes care of clearing cloned data */
		~XmlParseMaster();

		/**	@brief Obtain a new copy of this instance. Data will be deep copied and will need to reset in case it already contains data.
		*	User is responsible for deleting the clone
		*	@return Address of the clone
		*/
		XmlParseMaster* Clone() const;

		/**	@brief Add a new helper to the parser
		*	@param address of the helper
		*/
		void AddHelper(IXmlParseHelper& helperObject);
		
		/**	@brief Removes the helper from the parser. User is responsible for deleting the helper.
		*	@param address of the helper
		*/
		void RemoveHelper(IXmlParseHelper& helperObject); 

		/**	@brief Parse the string using Expat
		*	@param the string of xml to parse
		*	@param the length of the string
		*	@param if it is the first piece of data fed to the system, required to initialise the system before use
		*	@param if it is the last piece of data, required to inform Expat to stop parsing more data
		*	@throws std::exception, if the xml is invalid
		*/
		void Parse(const char* data, unsigned int length, bool isFirstChunk, bool isLastChunk);

		/**	@brief Method to parse an xml file
		*	@param the path to the file
		*	@throws std::exception, if the xml is invalid
		*/
		void ParseFromFile(const std::string& fileName);

		/**	@brief Get the file name parsed by the system
		*	@return filename
		*/
		const std::string& GetFileName() const;

		/**	@brief Get the shared data passed around by the system
		*	@return address of the shared data
		*/
		SharedData* GetSharedData() const;

		/**	@brief Set the shared data for the system
		*	@param address of the shared data
		*/
		void SetSharedData(SharedData* sharedData);

		/**	@brief sets if exception should be thrown when failed to parse and xml
		*	@param true, if exceptions should be thrown
		*/
		void SetExceptionOnHandleFailure(bool value);

		/**	@brief gets if exception will be thrown when failed to parse and xml
		*	@param true, if exceptions will be thrown
		*/
		bool ExceptionOnHandleFailure() const;

		/**	@brief Marked delete to disallow. Use Clone() to obtain a new copy */
		XmlParseMaster(const XmlParseMaster& rhs) = delete;
		
		/**	@brief Marked delete to disallow. Use Clone() to obtain a new copy */
		XmlParseMaster& operator=(const XmlParseMaster& rhs) = delete;
		
		/**	@brief Resets the members except the shared data */
		void Reset();

		/**	@brief returns if the instance is a clone
		*	@return true if it is a clone, false otherwise
		*/
		bool IsClone() const;

	private:
		std::string mFileName;
		SharedData* mSharedData;
		XML_Parser mXmlParser;
		bool mIsClone;
		SList<IXmlParseHelper*> mHelpers;
		bool mExceptionOnHandleFailed;

		/* Handlers for Expat */
		static void StartElementHandler(void* userData, const char* tagName, const char** attributes);
		static void EndElementHandler(void* userData, const char* tagName);
		static void CharDataHandler(void* userData, const char* innerText, int length);
	};
}
