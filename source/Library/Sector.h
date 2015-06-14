/**	@file Sector.h
*	Declaration of Sector and SectorFactory
*/
#pragma once
#include "Entity.h"
#include "WorldState.h"

namespace Library
{
	class World;

	/**	@class Sector
	*	Represents an portion of the world. Consists of entities. Can also contain actions.
	*/
	class Sector final : public Attributed
	{
		RTTI_DECLARATIONS(Sector, Attributed)

		friend class World; //to allow world to modify its name
	public:
		/**	@brief Constructor that initialises members and sets the name. Name cannot be set elsewhere using setters. */
		Sector(const std::string& name="");

		/** @brief Default destructor to release memory used by members */
		virtual ~Sector() = default;

		/**	@brief Returns the name of the sector
		*	@return name of the sector
		*/
		const std::string& Name() const;
		
		/**	@brief Return the scope of Entities in this sector
		*	@return scope containing the entities in the sector
		*/
		Scope* Entities() const;

		/**	@brief Create an entity using its factory, specified by the class name and assign it the name. Also add the entity to the world
		*	@return The new entity
		*	@param factory name of the entity
		*	@param name of the new entity
		*/
		Entity* CreateEntity(const std::string& className, const std::string& instanceName);

		/**	@brief Sets the world the sector is in and essentially moves it into that world
		*	@param the world to add it to
		*/
		void SetWorld(World& world);

		/**	@brief Returns the world the sector belongs to
		*	@return the parent world
		*/
		World* GetWorld() const;

		/**	@brief Update the sector based on the state of the world. Calls update on its entities
		*	@param state of the world
		*/
		void Update(WorldState& worldState);
		
		//copying is not allowed
		Sector(const Sector& rhs) = delete;
		Sector& operator=(const Sector& rhs) = delete;

		/**	@brief Return the actions in this sector
		*	@return scope containing the actions in the sector
		*/
		Scope* Actions() const;

		/**	@brief Create an action using its factory and assign it the name. Also add the action to the sector
		*	@return The new action
		*	@param class name of the new action
		*	@param name of the new action
		*/
		Action* CreateAction(const std::string& className, const std::string& instanceName);

	private:
		std::string mName;
		Scope* mEntities;
		Scope* mActions;
		World* mWorld;
	};

	CONCRETE_FACTORY(Sector,RTTI)
}