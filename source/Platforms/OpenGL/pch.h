/**	@file pch.h
*	Pre-compiled header file to include necessary header for OpenGL version of the game engine
*/
#pragma once

#define WIN32_LEAN_AND_MEAN  
#include <windows.h>
#include <exception>
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include <memory>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include "OpenGL.h"
#include "targetver.h"

#include "GL/gl3w.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
