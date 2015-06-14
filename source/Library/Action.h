/**	@file Action.h
*	@brief Declarations of Action
*/

#pragma once
#include "Attributed.h"
#include "WorldState.h"
#include "ConcreteFactory.h"

namespace Library
{
	/**	@class Action
	*	@brief Defines a verb that an entity, world or sector can perform
	*/
	class Action : public Attributed
	{
		RTTI_DECLARATIONS(Action, Attributed)

		//to allow these classes to access private mName
		friend class World;
		friend class Entity;
		friend class Sector;

	public:
		/**	@brief Constructor that takes in an optional name for the action */
		Action(const std::string& name = "");

		/**	@brief Default destructor to release memory held by members */
		virtual ~Action() = default;

		/**	@brief Return the scope of subactions in this action
		*	@return scope containing the subaction in the action
		*/
		Scope* SubActions() const;

		/**	@brief Performs an action
		*	@param state of the world
		*/
		virtual void Update(WorldState& worldState) = 0;

		/**	@brief Sets the entity the action is in and moves it into that entity
		*	@param the entity to add it to
		*/
		void SetEntity(Entity& entity);

		/**	@brief Sets the world the action is in and moves it into that world
		*	@param the world to add it to
		*/
		void SetWorld(World& world);

		/**	@brief Sets the sector the action is in and moves it into that sector
		*	@param the sector to add it to
		*/
		void SetSector(Sector& sector);

		/**	@brief Sets the action the subaction is in and moves it into that action
		*	@param the action to add it to
		*/
		void SetAction(Action& action);

		/**	@brief Returns the entity the action belongs to
		*	@return the parent entity
		*/
		Entity* GetEntity() const;

		/**	@brief Returns the action the action belongs to, if it is subaction
		*	@return the parent action
		*/
		Action* GetAction() const;

		/**	@brief Returns the sector the action belongs to
		*	@return the parent sector
		*/
		Sector* GetSector() const;

		/**	@brief Returns the world the action belongs to
		*	@return the parent world
		*/
		World* GetWorld() const;

		/**	@brief Create an action using its factory and assign it the name. Also add the action as a subaction to this action
		*	@return The new action
		*	@param class name of the new action
		*	@param name of the new action
		*/
		Action* CreateSubAction(const std::string& className, const std::string& instanceName);

		/**	@brief Returns the name of the action
		*	@return name of the action
		*/
		const std::string& Name() const;

		//dis-allowing copying
		Action(const Action& rhs) = delete;
		Action& operator=(const Action& rhs) = delete;

	protected:
		std::string mName;
		World* mWorld;
		Sector* mSector;
		Entity* mEntity;
		Action* mAction;
		Scope* mSubActions;
	};

#define ACTION_FACTORY(ActionType) \
	CONCRETE_FACTORY(ActionType, Action)
}
