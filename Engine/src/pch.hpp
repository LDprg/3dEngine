/*****************************************************************/ /**
 * \file   pch.hpp
 * \brief  Precompiled header
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

#include <any>
#include <initializer_list>
#include <memory>
#include <queue>
#include <utility>

#include <BasicTypes.h>
#include <Graphics/GraphicsTools/interface/MapHelper.hpp>

#include <Engine/Core/Application.hpp>

#include <GLFW/glfw3.h>

//#if LINUX
//#define GLFW_EXPOSE_NATIVE_X11
//#elif WINDOWS
//#define GLFW_EXPOSE_NATIVE_WIN32
//#elif OSX
//#define GLFW_EXPOSE_NATIVE_COCOA
//#endif

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <glm/glm.hpp>

#include <entt/entt.hpp>
