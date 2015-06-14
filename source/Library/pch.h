/**	@file pch.h
*	Pre-compiled header file to include necessary header for the game engine Library
*/
#pragma once

#include "targetver.h"

#include <algorithm>
#include <string>
#include <sstream>
#include <chrono>
#include <memory>
#include <thread>
#include <mutex>
#include <future>

#include "glm/glm.hpp"
#include "glm/gtx/string_cast.hpp"

#include "hashmap.h"
#include "Slist.h"
#include "stack.h"
#include "vector.h"
#include "DefaultVectorFunctor.h"
#include "DefaultHashFunctor.h"

#include "RTTI.h"
#include "Datum.h"
#include "Scope.h"
#include "Attributed.h"

#include "IXmlParseHelper.h"
#include "XmlParseMaster.h"

#include "TableSharedData.h"
#include "XmlParseHelperTable.h"
#include "XmlParseHelperAction.h"

#include "Factory.h"
#include "ConcreteFactory.h"

#include "Entity.h"
#include "Sector.h"
#include "World.h"
#include "WorldState.h"

#include "GameTime.h"
#include "GameClock.h"

#include "Action.h"
#include "ActionList.h"
#include "ActionIf.h"
#include "IncrementAction.h"
#include "DecrementAction.h"

#include "Event.h"
#include "EventPublisher.h"
#include "EventSubscriber.h"
#include "EventQueue.h"

#include "ActionEvent.h"
#include "EventMessageAttributed.h"
#include "Reaction.h"
#include "ReactionAttributed.h"

#define WIN32_LEAN_AND_MEAN   
