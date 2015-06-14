/**	@file Entity.h
*	Declaration of Entity and EntityFactory
*/
#pragma once
#include "WorldState.h"
#include "Scope.h"
#include "Attributed.h"
#include "ConcreteFactory.h"
#include "Action.h"

namespace Library
{
	class Sector;

	/**	@class Entity
	*	Represents an entity in the world. Consists of actions.
	*/
	class Entity : public Attributed
	{
		RTTI_DECLARATIONS(Entity, Attributed)

		friend class Sector; //to allow sector to modify name

	public:
		/**	@brief Constructor that initialises members and sets the name. Name cannot be set elsewhere using setters. */
		Entity(const std::string& name="");

		/** @brief Default destructor to release memory used by members */
		virtual ~Entity() = default;

		/**	@brief Returns the name of the entity
		*	@return name of the entity
		*/
		const std::string& Name() const;
		
		/**	@brief Returns the sector the entity belongs to
		*	@return the parent sector
		*/
		Sector* GetSector() const;

		/**	@brief Sets the sector the entity is in and essentially moves it into that sector 
		*	@param the sector to add it to
		*/
		void SetSector(Sector& sector);

		/**	@brief Update the entity based on the state of the world. Call update on its actions.
		*	@param state of the world
		*/
		virtual void Update(WorldState& worldState);
		
		/**	@brief Return the scope of Actions in this entity
		*	@return scope containing the actions for the entity
		*/
		Scope* Actions() const;

		//dis-allowing copying
		Entity(const Entity& rhs) = delete;
		Entity& operator=(const Entity& rhs) = delete;

		/**	@brief Create an action using its factory and assign it the name. Also add the action to the entity
		*	@return The new action
		*	@param class name of the new action
		*	@param name of the new action
		*/
		Action* CreateAction(const std::string& className, const std::string& instanceName);

	protected:
		std::string mName;
		Sector* mSector;
		Scope* mActions;
	};

	CONCRETE_FACTORY(Entity, RTTI)
}
