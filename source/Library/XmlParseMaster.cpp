/**	@file XmlParseMaster.cpp
*	@brief Implementation of SharedData and XmlParseMaster
*/

#include "pch.h"
#include "XmlParseMaster.h"
#include "IXmlParseHelper.h"
#include <fstream>

namespace Library
{
#pragma region XML Parse Master

	XmlParseMaster::XmlParseMaster(SharedData* sharedData, bool exceptionOnFail) :
		mFileName(), mXmlParser(XML_ParserCreate(NULL)), mIsClone(false), mHelpers(), mExceptionOnHandleFailed(exceptionOnFail)
	{
		SetSharedData(sharedData); //because other required operations are being done
	}

	XmlParseMaster::~XmlParseMaster()
	{
		if (mIsClone)
		{
			//delete the helpers
			for (auto& it : mHelpers)
			{
				delete it;
			}

			delete mSharedData;
		}
		
		mSharedData = nullptr;

		XML_ParserFree(mXmlParser);
	}

	XmlParseMaster* XmlParseMaster::Clone() const
	{
		XmlParseMaster* clone = new XmlParseMaster();

		if (mSharedData != nullptr)
		{
			clone->SetSharedData(mSharedData->Clone());
		}
		else
		{
			clone->SetSharedData(nullptr);
		}
		clone->mIsClone = true;

		/*XML_SetUserData(clone->mXmlParser, clone->mSharedData);
		XML_SetCharacterDataHandler(clone->mXmlParser, clone->CharDataHandler);
		XML_SetElementHandler(clone->mXmlParser, clone->StartElementHandler, clone->EndElementHandler);*/

		//Populate helpers list with clones
		for (auto& it : mHelpers)
		{
			clone->mHelpers.PushBack(it->Create());
		}

		clone->mExceptionOnHandleFailed = mExceptionOnHandleFailed;
		return clone;
	}

	void XmlParseMaster::AddHelper(IXmlParseHelper& helperObject)
	{
		mHelpers.PushBack(&helperObject);
	}

	void XmlParseMaster::RemoveHelper(IXmlParseHelper& helperObject)
	{
		mHelpers.Remove(&helperObject);
	}

	void XmlParseMaster::Parse(const char* data, unsigned int length, bool isFirstChunk, bool isLastChunk)
	{
		if (data == nullptr)
		{
			throw std::exception("Null data");
		}

		if (isFirstChunk)
		{
			Reset();
		}

		if (XML_Parse(mXmlParser, data, length, isLastChunk) != XML_STATUS_OK && mExceptionOnHandleFailed)
		{
			throw std::exception("Error while parsing XML");
		}
	}

	void XmlParseMaster::ParseFromFile(const std::string& fileName)
	{
		if (fileName.empty())
		{
			throw std::exception("Empty file name");
		}

		bool isFirstChunk = true;
		std::ifstream xmlFile(fileName,  std::ifstream::in);
		std::string fileInput;

		if (!xmlFile.bad() && xmlFile.is_open())
		{
			//read a line from the file
			while (!xmlFile.eof())
			{
				std::getline(xmlFile, fileInput);
				Parse(fileInput.c_str(), fileInput.length(), isFirstChunk, xmlFile.eof());

				isFirstChunk = false;
			}

			xmlFile.close();
		}
		else
		{
			xmlFile.close();
			throw std::exception("Cant open file");
		}
	}

	const std::string& XmlParseMaster::GetFileName() const
	{
		return mFileName;
	}

	XmlParseMaster::SharedData* XmlParseMaster::GetSharedData() const 
	{
		return mSharedData;
	}

	void XmlParseMaster::SetSharedData(SharedData* sharedData)
	{
		mSharedData = sharedData;
		
		if (sharedData != nullptr)
		{
			sharedData->SetXmlParseMaster(this);
		}

		XML_SetUserData(mXmlParser, mSharedData);
	}

	void XmlParseMaster::StartElementHandler(void* userData, const char* tagName, const char** attributes)
	{
		if (userData == nullptr)
		{
			throw std::exception("Shared data not set");
		}

		bool wasHandled = false;
		HashMap<std::string, std::string> attributeList;

		//parse attributes into hashmap
		if (attributes != nullptr)
		{
			int i = 0;
			
			std::string key;

			while (attributes[i]!=nullptr)
			{
				key = attributes[i];
				attributeList.Insert(key, attributes[i+1]);
				i+=2;
			}
		}

		SharedData* sharedData = reinterpret_cast<SharedData*>(userData);
		sharedData->IncrementDepth();
		
		XmlParseMaster* master = sharedData->GetXmlParseMaster();

		if (master == nullptr)
		{
			throw std::exception("Master is null in the shared data");
		}

		//walk through the list until true
		for (auto& it : master->mHelpers)
		{
			if ((*it).StartElementHandler(sharedData, tagName, attributeList))
			{
				wasHandled = true;
				break;
			}
		}

		if (!wasHandled && master->mExceptionOnHandleFailed)
		{
			throw std::exception("Call was not handled");
		}		
	}

	void XmlParseMaster::EndElementHandler(void* userData, const char* tagName)
	{
		if (userData == nullptr)
		{
			throw std::exception("Shared data not set");
		}

		SharedData* sharedData = reinterpret_cast<SharedData*>(userData);
		XmlParseMaster* master = sharedData->GetXmlParseMaster();
		
		if (master == nullptr)
		{
			throw std::exception("Master is null in the shared data");
		}

		bool wasHandled=false;

		//walk through the helpers
		for (auto& it : master->mHelpers)
		{
			if ((*it).EndElementHandler(sharedData, tagName))
			{
				wasHandled = true;
				break;
			}
		}

		if (!wasHandled && master->mExceptionOnHandleFailed)
		{
			throw std::exception("Call was not handled");
		}

		sharedData->DecrementDepth();
	}

	void XmlParseMaster::CharDataHandler(void* userData, const char* innerText, int length)
	{
		if (userData == nullptr)
		{
			throw std::exception("Shared data not set");
		}

		SharedData* sharedData = reinterpret_cast<SharedData*>(userData);
		XmlParseMaster* master = sharedData->GetXmlParseMaster();

		if (master == nullptr)
		{
			throw std::exception("Master is null in the shared data");
		}

		bool wasHandled=false;

		for (auto& it : master->mHelpers)
		{
			if ((*it).CharDataHandler(sharedData, std::string(innerText,length)))
			{
				wasHandled = true;
				break;
			}
		}

		if (!wasHandled && master->mExceptionOnHandleFailed)
		{
			throw std::exception("Call was not handled");
		}
	}

	void XmlParseMaster::SetExceptionOnHandleFailure(bool value)
	{
		mExceptionOnHandleFailed = value;
	}

	bool XmlParseMaster::ExceptionOnHandleFailure() const
	{
		return mExceptionOnHandleFailed;
	}

	void XmlParseMaster::Reset()
	{ 
		//reset shared data
		mSharedData->Initialise();

		//free and reset the parser
		XML_ParserFree(mXmlParser);
		mXmlParser=XML_ParserCreate(NULL);

		//reset handlers
		XML_SetUserData(mXmlParser, mSharedData);
		XML_SetCharacterDataHandler(mXmlParser, CharDataHandler);
		XML_SetElementHandler(mXmlParser, StartElementHandler, EndElementHandler);

		//walk through list and init helpers
		for (auto& it : mHelpers)
		{
			it->Initialize();
		}
	}

	bool XmlParseMaster::IsClone() const
	{
		return mIsClone;
	}
#pragma endregion

#pragma region Shared Data
	RTTI_DEFINITIONS(XmlParseMaster::SharedData)

	XmlParseMaster::SharedData::SharedData(XmlParseMaster* parseMaster) :
		mDepth(0), mXmlParseMaster(parseMaster)
	{
	}

	void XmlParseMaster::SharedData::SetXmlParseMaster(XmlParseMaster* parseMaster)
	{
		mXmlParseMaster = parseMaster;
	}

	XmlParseMaster* XmlParseMaster::SharedData::GetXmlParseMaster() const
	{
		return mXmlParseMaster;
	}

	void XmlParseMaster::SharedData::IncrementDepth()
	{
		++mDepth;
	}

	void XmlParseMaster::SharedData::DecrementDepth()
	{
		if (mDepth > 0)
		{
			--mDepth;
		}
	}

	std::uint32_t XmlParseMaster::SharedData::Depth() const
	{
		return mDepth;
	}

	void XmlParseMaster::SharedData::Initialise()
	{
		mDepth = 0;
	}
#pragma endregion
}