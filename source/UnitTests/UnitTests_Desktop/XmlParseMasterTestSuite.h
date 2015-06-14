#pragma once

#include <cxxtest/TestSuite.h>
#include "vld.h"

#include "pch.h"
#include "AssetParseHelper.h"
#include "AssetSharedData.h"
#include "ModelParseHelper.h"
#include "BodyPartParseHelper.h"
#include "MeshParseHelper.h"
#include "PositionParseHelper.h"

using namespace Library;
using namespace Test;

class XmlParseMasterTestSuite : public CxxTest::TestSuite
{
public:
	void TestConstruction()
	{
		XmlParseMaster master;
		AssetSharedData* sharedData = new AssetSharedData();
		master.SetSharedData(sharedData);
		TS_ASSERT_EQUALS(sharedData->Depth(), 0);
		TS_ASSERT_EQUALS(sharedData, master.GetSharedData());

		delete sharedData;
	}

	void TestParseBodyPart()
	{
		XmlParseMaster master;
		AssetSharedData* sharedData = new AssetSharedData();
		master.SetSharedData(sharedData);

		AssetParseHelper assetParser;
		ModelParseHelper modelParser;
		MeshParseHelper meshParser;
		BodyPartParseHelper bodyPartParser;
		PositionParseHelper positionParser;

		master.AddHelper(assetParser);
		master.AddHelper(bodyPartParser);
		master.AddHelper(modelParser);
		master.AddHelper(meshParser);
		master.AddHelper(positionParser);

		std::string xmlString = "<bodyPart>leg</bodyPart>";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);

		TS_ASSERT_EQUALS(sharedData->mCharHandlerCallCount, 1);
		TS_ASSERT_EQUALS(sharedData->mStartHandlerCallCount, 1);
		TS_ASSERT_EQUALS(sharedData->mEndHandlerCallCount, 1);

		TS_ASSERT_EQUALS(sharedData->Depth(), 0);
		TS_ASSERT_EQUALS(sharedData->mMaxDepth, 1);

		TS_ASSERT_EQUALS(sharedData->mMeshAttributeList.Size(), 0);
		TS_ASSERT_EQUALS(sharedData->mModelAttributeList.Size(), 0); 
		TS_ASSERT_EQUALS(sharedData->mCharDataList.Size(), 1);

		xmlString = "<bodyPart part=\"leg\" />";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);

		TS_ASSERT_EQUALS(sharedData->mCharHandlerCallCount, 1);
		TS_ASSERT_EQUALS(sharedData->mStartHandlerCallCount, 2);
		TS_ASSERT_EQUALS(sharedData->mEndHandlerCallCount, 2);

		TS_ASSERT_EQUALS(sharedData->Depth(), 0);
		TS_ASSERT_EQUALS(sharedData->mMaxDepth, 1);

		TS_ASSERT_EQUALS(sharedData->mMeshAttributeList.Size(), 0);
		TS_ASSERT_EQUALS(sharedData->mModelAttributeList.Size(), 0);
		TS_ASSERT_EQUALS(sharedData->mCharDataList.Size(), 1);

		delete sharedData;
	}

	void TestParseMesh()
	{
		XmlParseMaster master;
		AssetSharedData* sharedData = new AssetSharedData();
		master.SetSharedData(sharedData);

		AssetParseHelper assetParser;
		ModelParseHelper modelParser;
		MeshParseHelper meshParser;
		BodyPartParseHelper bodyPartParser;
		PositionParseHelper positionParser;

		master.AddHelper(assetParser);
		master.AddHelper(bodyPartParser);
		master.AddHelper(modelParser);
		master.AddHelper(meshParser);
		master.AddHelper(positionParser);

		std::string xmlString = "<mesh name=\"Head\" collider=\"sphere\" />";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);

		TS_ASSERT_EQUALS(sharedData->mCharHandlerCallCount, 0);
		TS_ASSERT_EQUALS(sharedData->mStartHandlerCallCount, 1);
		TS_ASSERT_EQUALS(sharedData->mEndHandlerCallCount, 1);

		TS_ASSERT_EQUALS(sharedData->Depth(), 0);
		TS_ASSERT_EQUALS(sharedData->mMaxDepth, 1);

		TS_ASSERT_EQUALS(sharedData->mMeshAttributeList.Size(), 1);
		TS_ASSERT_EQUALS(sharedData->mModelAttributeList.Size(), 0);
		TS_ASSERT_EQUALS(sharedData->mCharDataList.Size(), 0);

		xmlString = "<mesh name=\"hand\" collider=\"capsule\"><bodyPart>hand</bodyPart></mesh>";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);

		TS_ASSERT_EQUALS(sharedData->mCharHandlerCallCount, 1);
		TS_ASSERT_EQUALS(sharedData->mStartHandlerCallCount, 3);
		TS_ASSERT_EQUALS(sharedData->mEndHandlerCallCount, 3);

		TS_ASSERT_EQUALS(sharedData->Depth(), 0);
		TS_ASSERT_EQUALS(sharedData->mMaxDepth, 2);

		TS_ASSERT_EQUALS(sharedData->mMeshAttributeList.Size(), 2);
		TS_ASSERT_EQUALS(sharedData->mModelAttributeList.Size(), 0);
		TS_ASSERT_EQUALS(sharedData->mCharDataList.Size(), 1);

		delete sharedData;
	}

	void TestParsePosition()
	{
		XmlParseMaster master;
		AssetSharedData* sharedData = new AssetSharedData();
		master.SetSharedData(sharedData);

		AssetParseHelper assetParser;
		ModelParseHelper modelParser;
		MeshParseHelper meshParser;
		BodyPartParseHelper bodyPartParser;
		PositionParseHelper positionParser;

		master.AddHelper(assetParser);
		master.AddHelper(bodyPartParser);
		master.AddHelper(modelParser);
		master.AddHelper(meshParser);
		master.AddHelper(positionParser);

		std::string xmlString = "<position><x>10</x><y>20</y><z>-10</z></position>";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);

		TS_ASSERT_EQUALS(sharedData->mCharHandlerCallCount, 3);
		TS_ASSERT_EQUALS(sharedData->mStartHandlerCallCount, 4);
		TS_ASSERT_EQUALS(sharedData->mEndHandlerCallCount, 4);

		TS_ASSERT_EQUALS(sharedData->Depth(), 0);
		TS_ASSERT_EQUALS(sharedData->mMaxDepth, 2);

		TS_ASSERT_EQUALS(sharedData->mMeshAttributeList.Size(), 0);
		TS_ASSERT_EQUALS(sharedData->mModelAttributeList.Size(), 0);
		TS_ASSERT_EQUALS(sharedData->mCharDataList.Size(), 3);

		delete sharedData;
	}

	void TestParseModel()
	{
		XmlParseMaster master;
		AssetSharedData* sharedData = new AssetSharedData();
		master.SetSharedData(sharedData);

		AssetParseHelper assetParser;
		ModelParseHelper modelParser;
		MeshParseHelper meshParser;
		BodyPartParseHelper bodyPartParser;
		PositionParseHelper positionParser;

		master.AddHelper(assetParser);
		master.AddHelper(bodyPartParser);
		master.AddHelper(modelParser);
		master.AddHelper(meshParser);
		master.AddHelper(positionParser);

		std::string xmlString = "<model path=\"somewhere\">   </model>";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);

		TS_ASSERT_EQUALS(sharedData->mCharHandlerCallCount, 1);
		TS_ASSERT_EQUALS(sharedData->mStartHandlerCallCount, 1);
		TS_ASSERT_EQUALS(sharedData->mEndHandlerCallCount, 1);

		TS_ASSERT_EQUALS(sharedData->Depth(), 0);
		TS_ASSERT_EQUALS(sharedData->mMaxDepth, 1);

		TS_ASSERT_EQUALS(sharedData->mMeshAttributeList.Size(), 0);
		TS_ASSERT_EQUALS(sharedData->mModelAttributeList.Size(), 1);
		TS_ASSERT_EQUALS(sharedData->mCharDataList.Size(),1);

		delete sharedData;
	}

	void TestParseAsset()
	{
		XmlParseMaster master;
		AssetSharedData* sharedData = new AssetSharedData();
		master.SetSharedData(sharedData);

		AssetParseHelper assetParser;
		ModelParseHelper modelParser;
		MeshParseHelper meshParser;
		BodyPartParseHelper bodyPartParser;
		PositionParseHelper positionParser;

		master.AddHelper(assetParser);
		master.AddHelper(bodyPartParser);
		master.AddHelper(modelParser);
		master.AddHelper(meshParser);
		master.AddHelper(positionParser);

		std::string xmlString = "<asset>   </asset>";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);

		TS_ASSERT_EQUALS(sharedData->mCharHandlerCallCount, 1);
		TS_ASSERT_EQUALS(sharedData->mStartHandlerCallCount, 1);
		TS_ASSERT_EQUALS(sharedData->mEndHandlerCallCount, 1);

		TS_ASSERT_EQUALS(sharedData->Depth(), 0);
		TS_ASSERT_EQUALS(sharedData->mMaxDepth, 1);

		TS_ASSERT_EQUALS(sharedData->mMeshAttributeList.Size(), 0);
		TS_ASSERT_EQUALS(sharedData->mModelAttributeList.Size(), 0);
		TS_ASSERT_EQUALS(sharedData->mCharDataList.Size(), 1);

		delete sharedData;
	}

	void TestParseOtherTag()
	{
		XmlParseMaster master(nullptr,true);
		AssetSharedData* sharedData = new AssetSharedData();
		master.SetSharedData(sharedData);

		AssetParseHelper assetParser;
		ModelParseHelper modelParser;
		MeshParseHelper meshParser;
		BodyPartParseHelper bodyPartParser;
		PositionParseHelper positionParser;

		master.AddHelper(assetParser);
		master.AddHelper(bodyPartParser);
		master.AddHelper(modelParser);
		master.AddHelper(meshParser);
		master.AddHelper(positionParser);

		std::string xmlString = "<other>data</other>";
		TS_ASSERT_THROWS(master.Parse(xmlString.c_str(), xmlString.length(), true, true), std::exception);

		delete sharedData;
	}

	void TestParseFromFile()
	{
		XmlParseMaster master;
		AssetSharedData* sharedData = new AssetSharedData();
		master.SetSharedData(sharedData);

		AssetParseHelper assetParser;
		ModelParseHelper modelParser;
		MeshParseHelper meshParser;
		BodyPartParseHelper bodyPartParser;
		PositionParseHelper positionParser;

		master.AddHelper(assetParser);
		master.AddHelper(bodyPartParser);
		master.AddHelper(modelParser);
		master.AddHelper(meshParser);
		master.AddHelper(positionParser);

		master.ParseFromFile("Data/AssetList.xml");

		TS_ASSERT_EQUALS(sharedData->mCharHandlerCallCount, 8);
		TS_ASSERT_EQUALS(sharedData->mStartHandlerCallCount, 14);
		TS_ASSERT_EQUALS(sharedData->mEndHandlerCallCount, 14);

		TS_ASSERT_EQUALS(sharedData->Depth(), 0);
		TS_ASSERT_EQUALS(sharedData->mMaxDepth, 5);

		TS_ASSERT_EQUALS(sharedData->mMeshAttributeList.Size(), 2);
		TS_ASSERT_EQUALS(sharedData->mModelAttributeList.Size(), 1);
		TS_ASSERT_EQUALS(sharedData->mCharDataList.Size(), 8);

		delete sharedData;
	}

	void TestParseXmlInFile()
	{
		XmlParseMaster master;
		AssetSharedData* sharedData = new AssetSharedData();
		master.SetSharedData(sharedData);

		AssetParseHelper assetParser;
		ModelParseHelper modelParser;
		MeshParseHelper meshParser;
		BodyPartParseHelper bodyPartParser;
		PositionParseHelper positionParser;

		master.AddHelper(assetParser);
		master.AddHelper(bodyPartParser);
		master.AddHelper(modelParser);
		master.AddHelper(meshParser);
		master.AddHelper(positionParser);

		std::string xmlString = "<asset>"
			"<model path = \"resources\">"
			"<mesh name = \"left arm\" collider = \"capsule\">"
			"<bodyPart>arm</bodyPart>"
			"<position>"
			"<x>1</x><y>1</y><z>1</z>"
			"</position>"
			"</mesh>"
			"<mesh name = \"right arm\" collider = \"capsule\">"
			"<bodyPart>arm</bodyPart>"
			"<position>"
			"<x>-1</x><y>-1</y><z>-1</z>"
			"</position>"
			"</mesh>"
			"</model>"
			"</asset>";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);

		TS_ASSERT_EQUALS(sharedData->mCharHandlerCallCount, 8);
		TS_ASSERT_EQUALS(sharedData->mStartHandlerCallCount, 14);
		TS_ASSERT_EQUALS(sharedData->mEndHandlerCallCount, 14);

		TS_ASSERT_EQUALS(sharedData->Depth(), 0);
		TS_ASSERT_EQUALS(sharedData->mMaxDepth, 5);

		TS_ASSERT_EQUALS(sharedData->mMeshAttributeList.Size(), 2);
		TS_ASSERT_EQUALS(sharedData->mModelAttributeList.Size(), 1);
		TS_ASSERT_EQUALS(sharedData->mCharDataList.Size(), 8);

		delete sharedData;
	}

	void TestInvalidXML()
	{
		XmlParseMaster master(nullptr,true);
		AssetSharedData* sharedData = new AssetSharedData();
		master.SetSharedData(sharedData);

		AssetParseHelper assetParser;
		ModelParseHelper modelParser;
		MeshParseHelper meshParser;
		BodyPartParseHelper bodyPartParser;
		PositionParseHelper positionParser;

		master.AddHelper(assetParser);
		master.AddHelper(bodyPartParser);
		master.AddHelper(modelParser);
		master.AddHelper(meshParser);
		master.AddHelper(positionParser);

		std::string xmlString = "";
		TS_ASSERT_THROWS(master.Parse(xmlString.c_str(), xmlString.length(), true, true), std::exception);

		xmlString = "</asset>";
		TS_ASSERT_THROWS(master.Parse(xmlString.c_str(), xmlString.length(), true, true), std::exception);

		xmlString = "<hello>";
		TS_ASSERT_THROWS(master.Parse(xmlString.c_str(), xmlString.length(), true, true), std::exception);

		xmlString = "string";
		TS_ASSERT_THROWS(master.Parse(xmlString.c_str(), xmlString.length(), true, true), std::exception);

		xmlString = "<z/><z/>";
		TS_ASSERT_THROWS(master.Parse(xmlString.c_str(), xmlString.length(), true, true), std::exception);

		xmlString = "<z><x></z>";
		TS_ASSERT_THROWS(master.Parse(xmlString.c_str(), xmlString.length(), true, true), std::exception);

		delete sharedData;
	}

	void TestClone()
	{
		XmlParseMaster master;
		AssetSharedData* sharedData = new AssetSharedData();
		master.SetSharedData(sharedData);

		AssetParseHelper assetParser;
		ModelParseHelper modelParser;
		MeshParseHelper meshParser;
		BodyPartParseHelper bodyPartParser;
		PositionParseHelper positionParser;

		master.AddHelper(assetParser);
		master.AddHelper(bodyPartParser);
		master.AddHelper(modelParser);
		master.AddHelper(meshParser);
		master.AddHelper(positionParser);

		std::string xmlString = "<bodyPart>torso</bodyPart>";
		master.Parse(xmlString.c_str(), xmlString.length(), true, true);

		TS_ASSERT_EQUALS(sharedData->mCharHandlerCallCount, 1);
		TS_ASSERT_EQUALS(sharedData->mStartHandlerCallCount, 1);
		TS_ASSERT_EQUALS(sharedData->mEndHandlerCallCount, 1);

		TS_ASSERT_EQUALS(sharedData->Depth(), 0);
		TS_ASSERT_EQUALS(sharedData->mMaxDepth, 1);

		TS_ASSERT_EQUALS(sharedData->mMeshAttributeList.Size(), 0);
		TS_ASSERT_EQUALS(sharedData->mModelAttributeList.Size(), 0);
		TS_ASSERT_EQUALS(sharedData->mCharDataList.Size(), 1);

		//test clone master
		XmlParseMaster* newMaster = master.Clone();
		TS_ASSERT_EQUALS(newMaster->GetFileName(), master.GetFileName());
		TS_ASSERT_EQUALS(newMaster->GetSharedData()->Depth(), master.GetSharedData()->Depth());
		TS_ASSERT(newMaster->IsClone());

		//test clone helper
		AssetParseHelper* newParseHelper = reinterpret_cast<AssetParseHelper*>(assetParser.Create());
		TS_ASSERT_DIFFERS(newParseHelper, &assetParser);

		//test clone shared data
		AssetSharedData* newSharedData = reinterpret_cast<AssetSharedData*>(sharedData->Clone());
		TS_ASSERT_DIFFERS(newSharedData->mMaxDepth, sharedData->mMaxDepth);

		TS_ASSERT_DIFFERS(newSharedData->mCharDataList.Size(), sharedData->mCharDataList.Size());
		TS_ASSERT_DIFFERS(newSharedData->mStartHandlerCallCount, sharedData->mStartHandlerCallCount);
		TS_ASSERT_DIFFERS(newSharedData->mEndHandlerCallCount, sharedData->mEndHandlerCallCount);
		TS_ASSERT_DIFFERS(newSharedData->mCharHandlerCallCount, sharedData->mCharHandlerCallCount);

		delete sharedData;
		delete newMaster;
		delete newParseHelper;
		delete newSharedData;
	}

	void TestRemoveHelper()
	{
		XmlParseMaster master(nullptr,true);
		AssetSharedData* sharedData = new AssetSharedData();
		master.SetSharedData(sharedData);

		AssetParseHelper assetParser;
		ModelParseHelper modelParser;
		MeshParseHelper meshParser;
		BodyPartParseHelper bodyPartParser;
		PositionParseHelper positionParser;

		master.AddHelper(assetParser);
		master.AddHelper(bodyPartParser);
		master.AddHelper(modelParser);
		master.AddHelper(meshParser);
		master.AddHelper(positionParser);

		master.RemoveHelper(meshParser);

		//test that request falls off the chain after helper is removed
		std::string xmlString = "<mesh name=\"Body\" collider=\"capsule\" />";
		TS_ASSERT_THROWS(master.Parse(xmlString.c_str(), xmlString.length(), true, true), std::exception);

		delete sharedData;
	}
};