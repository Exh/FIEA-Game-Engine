/**	@file WorldState.h
*	Declaration for WorldState class
*/

#pragma once
#include "GameTime.h"

namespace Library
{
	class World;
	class Sector;
	class Entity;
	class Action;

	/**	@class WorldState
	*	@brief Hold the state of the world, sector, entity and action. Also hold a game time. It is basically used as an activation record.
	*/
	class WorldState
	{
	public:
		/**	@brief Default constructor */
		WorldState();

		/**	@brief Default destructor */
		~WorldState()=default;

		World* mWorld;
		Sector* mSector;
		Entity* mEntity;
		Action* mAction;
		GameTime* mGameTime;

		/**	@brief for deep copying of one worldstate into another
		*	@param the worldstate to copy from
		*/
		WorldState& operator=(const WorldState& rhs);

		/**	@brief for deep copying of one worldstate into another
		*	@param the worldstate to copy from
		*/
		WorldState(const WorldState& rhs);

		/**	@brief to check if the two states are the same
		*	@param the state to check with
		*	@return true, if they are the same, false otherwise
		*/
		bool operator==(const WorldState& rhs);
		
		/**	@brief to check if the two states are different
		*	@param the state to check with
		*	@return true, if they are different, false otherwise
		*/
		bool operator!=(const WorldState& rhs);
	};
}
