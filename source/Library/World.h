/**	@file World.h
*	Declaration of World
*/
#pragma once
#include "Sector.h"
#include "GameTime.h"
#include "GameClock.h"
#include "WorldState.h"
#include "EventQueue.h"

namespace Library
{
	/**	@class Sector
	*	Represents the entire game world. Consists of sectors. Can also contain actions.
	*/
	class World final : public Attributed
	{
		RTTI_DECLARATIONS(World, Attributed)

	public:
		/**	@brief Constructor that initialises members and sets the name. */
		World(const std::string& name="");

		/** @brief Default destructor to release memory used by members */
		virtual ~World() = default;

		/**	@brief Return the scope of Sectors in this world
		*	@return scope containing the sectors in the world
		*/
		Scope* Sectors() const;

		/**	@brief Create a sector using its factory and assign it the name. Also add the sector to the world
		*	@return The new sector
		*	@param name of the new sector
		*/
		Sector* CreateSector(const std::string& instanceName);

		/**	@brief Update the world. Calls update on its sectors */
		void Update();

		/**	@brief Returns the name of the world
		*	@return name of the world
		*/
		const std::string& Name() const;
		
		/**	@brief Change the name of the world
		*	@param new name of the world
		*/
		void SetName(const std::string& name);

		/**	@brief Return the actions in this world
		*	@return scope containing the actions in the world
		*/
		Scope* Actions() const;

		//preventing copying
		World(const World& rhs) = delete;
		World& operator=(const World& rhs) = delete;

		/**	@brief Create an action using its factory and assign it the name. Also add the action to the world
		*	@return The new action
		*	@param class name of the new action
		*	@param name of the new action
		*/
		Action* CreateAction(const std::string& className, const std::string& instanceName);

		/**	@brief Accessor for the world state
		*	@return the world state
		*/
		const WorldState& GetWorldState() const;

		/**	@brief Accessor for the event queue
		*	@return the event queue
		*/
		const EventQueue& GetEventQueue() const;

		/**	@brief Accessor for the game time
		*	@return the game time
		*/
		const GameTime& GetGameTime() const;

	private:
		std::string mName;
		Scope* mSectors;
		Scope* mActions;
		WorldState mWorldState;

		GameTime mGameTime;
		GameClock mGameClock;

		EventQueue mEventQueue;
	};
}