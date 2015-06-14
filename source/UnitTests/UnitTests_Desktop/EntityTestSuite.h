#pragma once

#include <cxxtest/TestSuite.h>
#include "vld.h"

#include "pch.h"
#include "Kaijuu.h"
#include "Shujinko.h"
#include "LockedChest.h"

using namespace Library;
using namespace Test;

class EntityTestSuite : public CxxTest::TestSuite
{
public:
	//concrete factories are declared in respective class headers

	void TestConstruction()
	{
		World world("earth");
		TS_ASSERT_EQUALS(world.Size(), 4); //Contains this, name, sectors, actions
		TS_ASSERT_EQUALS(world.Name(), "earth");
		TS_ASSERT_EQUALS(world.Sectors()->Size(), 0);
			
		Sector sector("asia");
		TS_ASSERT_EQUALS(sector.Size(), 4); //Contains this, name, entities, actions
		TS_ASSERT_EQUALS(sector.Name(), "asia");
		TS_ASSERT_EQUALS(sector.Entities()->Size(), 0);

		Entity entity("japan");
		TS_ASSERT_EQUALS(entity.Size(), 3); //Contains this, name, actions
		TS_ASSERT_EQUALS(entity.Name(), "japan");
		TS_ASSERT_EQUALS(entity.Actions()->Size(), 0);
	}

	void TestEntitySetSector()
	{
		Sector sector("beach");
		Sector sector1("forest");
		Entity entity("coconut");

		TS_ASSERT_EQUALS(entity.GetSector(), nullptr);
		
		entity.SetSector(sector);
		TS_ASSERT_EQUALS(entity.GetSector(), &sector);
		TS_ASSERT_EQUALS(entity.GetSector()->Name(), "beach");

		//moving to another sector
		entity.SetSector(sector1);
		TS_ASSERT_EQUALS(entity.GetSector(), &sector1);
		TS_ASSERT_EQUALS(entity.GetSector()->Name(), "forest");
	}

	void TestCreateEntity()
	{
		KaijuuFactory kaiFactory;

		Sector wland("wonderland");
		Entity* alice = wland.CreateEntity("Kaijuu", "alice");

		TS_ASSERT_EQUALS(alice->Name(), "alice");

		TS_ASSERT_EQUALS(alice->GetSector(), &wland);

		TS_ASSERT(alice->Is("Kaijuu"));

		TS_ASSERT(wland.Entities()->Find("alice") != nullptr);
	}

	void TestSectorSetWorld()
	{
		World world("island");
		World world1("city");
		Sector sector("beach");
		
		Entity entity("coconut");
		entity.SetSector(sector);

		TS_ASSERT_EQUALS(sector.GetWorld(), nullptr);

		sector.SetWorld(world);
		TS_ASSERT_EQUALS(sector.GetWorld(), &world);
		TS_ASSERT_EQUALS(entity.GetSector()->GetWorld()->Name(), "island");
		
		//moving to another world
		sector.SetWorld(world1);
		TS_ASSERT_EQUALS(sector.GetWorld(), &world1);
		TS_ASSERT_EQUALS(entity.GetSector()->GetWorld()->Name(), "city");
	}

	void TestCreateSector()
	{
		SectorFactory sectorFactory;
	
		World world("stadium");
		Sector* sector = world.CreateSector("field");

		TS_ASSERT_EQUALS(sector->Name(), "field");

		TS_ASSERT_EQUALS(sector->GetWorld(), &world);

		TS_ASSERT(sector->Is("Sector"));

		TS_ASSERT(world.Sectors()->Find("field") != nullptr);
	}

	void TestCreateWithoutFactory()
	{
		World world;
		Sector sector;
		
		TS_ASSERT_EQUALS(world.CreateSector("a"),nullptr);
		TS_ASSERT_EQUALS(sector.CreateEntity("Kaijuu","a"), nullptr);

		XmlParseMaster master;
		World parsedWorld;

		TableSharedData sharedData(&parsedWorld);
		master.SetSharedData(&sharedData);

		XmlParseHelperTable helper;
		master.AddHelper(helper);

		//creating sector without factory from xml
		const std::string& xmlString = "<world name=\"world\"><sector name=\"x\" /></world>";
		TS_ASSERT_THROWS(master.Parse(xmlString.c_str(), xmlString.length(), true, true),std::exception);

		SectorFactory sFactory;

		//creating entity without factory from xml
		const std::string& xmlString1 = "<world name=\"world\"><sector name=\"it - sector\"><entity class=\"Shujinko\" name=\"Ram\" /></sector></world>";
		TS_ASSERT_THROWS(master.Parse(xmlString1.c_str(), xmlString1.length(), true, true), std::exception);
	}

	void TestCreateWorldFromXml()
	{
		const std::string& xmlString = "<world name=\"world\"></world>";

		XmlParseMaster master;
		World parsedWorld;

		TableSharedData sharedData(&parsedWorld);
		master.SetSharedData(&sharedData);

		XmlParseHelperTable helper;
		master.AddHelper(helper);

		//correct xml
		TS_ASSERT_EQUALS(parsedWorld.Name(), "");
		TS_ASSERT_THROWS_NOTHING(master.Parse(xmlString.c_str(), xmlString.length(), true, true));
		TS_ASSERT_EQUALS(parsedWorld.Name(), "world");

		//world inside other tags
		const std::string& xmlString1 = "<integer name=\"a\"><world name=\"world\"></world></integer>";
		TS_ASSERT_THROWS(master.Parse(xmlString1.c_str(), xmlString1.length(), true, true), std::exception);

		//world inside another world
		const std::string& xmlString2 = "<world name=\"a\"><world name=\"world\"></world></world>";
		TS_ASSERT_THROWS(master.Parse(xmlString2.c_str(), xmlString2.length(), true, true), std::exception);

		//trying to add a world to a scope
		Scope scope;
		TableSharedData sharedData1(&scope);
		master.SetSharedData(&sharedData1);
		TS_ASSERT_THROWS(master.Parse(xmlString.c_str(), xmlString.length(), true, true),std::exception);
	}

	void TestCreateSectorFromXml()
	{
		SectorFactory sectorFactory;

		const std::string& xmlString = "<world name=\"world\"><sector name=\"sector\" /></world>";

		XmlParseMaster master;
		World parsedWorld;

		TableSharedData sharedData(&parsedWorld);
		master.SetSharedData(&sharedData);

		XmlParseHelperTable helper;
		master.AddHelper(helper);

		//correct xml
		TS_ASSERT_THROWS_NOTHING(master.Parse(xmlString.c_str(), xmlString.length(), true, true));

		TS_ASSERT_EQUALS(parsedWorld.Sectors()->Size(), 1);
		
		auto* datum = parsedWorld.Sectors()->Find("sector");
		TS_ASSERT(datum != nullptr);

		Sector* sector = datum->GetTable(UINT32_MAX)->As<Sector>();
		TS_ASSERT(sector != nullptr);

		TS_ASSERT_EQUALS(sector->GetWorld(), &parsedWorld);

		//sector without a world -> ok since we're passing in a world
		const std::string& xmlString2 = "<sector name=\"sector1\" />";
		TS_ASSERT_THROWS_NOTHING(master.Parse(xmlString2.c_str(), xmlString2.length(), true, true));
		TS_ASSERT_EQUALS(parsedWorld.Sectors()->Size(), 2);

		//trying to add a sector to a scope
		Scope scope;
		TableSharedData sharedData1(&scope);
		master.SetSharedData(&sharedData1);
		const std::string& xmlString3 = "<sector name=\"sector2\" />";
		TS_ASSERT_THROWS(master.Parse(xmlString3.c_str(), xmlString3.length(), true, true), std::exception);
	}

	void TestCreateEntityFromXml()
	{
		ShujinkoFactory shuFactory;
		SectorFactory sFactory;

		const std::string& xmlString = "<world name=\"world\"><sector name=\"it - sector\"><entity class=\"Shujinko\" name=\"Ram\" /></sector></world>";

		XmlParseMaster master;
		World parsedWorld;

		TableSharedData sharedData(&parsedWorld);
		master.SetSharedData(&sharedData);

		XmlParseHelperTable helper;
		master.AddHelper(helper);

		//correct xml
		TS_ASSERT_THROWS_NOTHING(master.Parse(xmlString.c_str(), xmlString.length(), true, true));

		//validating sector
		TS_ASSERT_EQUALS(parsedWorld.Sectors()->Size(), 1);

		auto* datum = parsedWorld.Sectors()->Find("it - sector");
		TS_ASSERT(datum != nullptr);

		Sector* sector = datum->GetTable(UINT32_MAX)->As<Sector>();
		TS_ASSERT(sector != nullptr);

		TS_ASSERT_EQUALS(sector->GetWorld(), &parsedWorld);

		//validating entity
		TS_ASSERT_EQUALS(sector->Entities()->Size(), 1);

		auto* datum1 = sector->Entities()->Find("Ram");
		TS_ASSERT(datum1 != nullptr);

		Entity* entity = datum1->GetTable(UINT32_MAX)->As<Entity>();
		TS_ASSERT(entity != nullptr);

		TS_ASSERT_EQUALS(entity->GetSector(), sector);

		//entity without class attribute
		const std::string& xmlString1 = "<world name=\"world\"><sector name=\"it - sector\"><entity name=\"Ram\" /></sector></world>";
		TS_ASSERT_THROWS(master.Parse(xmlString1.c_str(), xmlString1.length(), true, true),std::exception);

		//entity tag that is not under a sector tag
		const std::string& xmlString2 = "<world name=\"world\"><entity name=\"Ram\" /></world>";
		TS_ASSERT_THROWS(master.Parse(xmlString2.c_str(), xmlString2.length(), true, true), std::exception);

		//trying to add an entity to a scope
		Scope scope;
		TableSharedData sharedData1(&scope);
		master.SetSharedData(&sharedData1);
		const std::string& xmlString3 = "<entity name=\"apple\" />";
		TS_ASSERT_THROWS(master.Parse(xmlString3.c_str(), xmlString3.length(), true, true), std::exception);
	}

	void TestCreateAll()
	{
		ShujinkoFactory shuFactory;
		SectorFactory sFactory;
		KaijuuFactory kaiFactory;
		LockedChestFactory chestFactory;

		XmlParseMaster master;
		World parsedWorld;

		TableSharedData sharedData(&parsedWorld);
		master.SetSharedData(&sharedData);

		XmlParseHelperTable helper;
		master.AddHelper(helper);

		TS_ASSERT_THROWS_NOTHING(master.ParseFromFile("Data/WorldXml.xml"));

		//world has 2 sectors and 2 more attributes
		TS_ASSERT_EQUALS(parsedWorld.Size(), 6); //4+2
		TS_ASSERT_EQUALS(parsedWorld.Sectors()->Size(), 2);

		//sector has 2 entities and 1 more attribute
		Sector* sector = parsedWorld.Sectors()->Find("Treasury")->GetTable()->As<Sector>();
		TS_ASSERT_EQUALS(sector->Size(), 5); //4+1
		TS_ASSERT_EQUALS(sector->Entities()->Size(), 3);

		//entity has 2 more attributes
		Entity* entity = sector->Entities()->Find("Guardian")->GetTable()->As<Entity>();
		TS_ASSERT_EQUALS(entity->Size(), 5);//3+2
	}

	void TestUpdate()
	{
		World world("world");
		Sector sector("sector");
		LockedChest entity("entity");
		WorldState tempState;

		sector.SetWorld(world);
		entity.SetSector(sector);

		TS_ASSERT_EQUALS(entity.mCallCount, 0);
		
		//entity's update
		entity.Update(tempState);
		TS_ASSERT_EQUALS(entity.mCallCount, 1);

		//sector's update
		sector.Update(tempState);
		TS_ASSERT_EQUALS(entity.mCallCount, 2);

		//world's update
		world.Update();
		TS_ASSERT_EQUALS(entity.mCallCount, 3);
	}
};