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

#include <Graphics/GraphicsEngine/interface/Buffer.h>
#include <Graphics/GraphicsEngine/interface/RenderDevice.h>
#include <Graphics/GraphicsEngine/interface/SwapChain.h>

#include <Imgui/interface/ImGuiDiligentRenderer.hpp>
#include <Imgui/interface/ImGuiImplDiligent.hpp>
#include <ThirdParty/imgui/imgui.h>

#include <Graphics/GraphicsTools/interface/MapHelper.hpp>
#include <Primitives/interface/BasicTypes.h>

#include <Common/interface/RefCntAutoPtr.hpp>

#include <GLFW/glfw3.h>

#if ENGINE_PLATFORM_LINUX
    #define GLFW_EXPOSE_NATIVE_X11
#elif ENGINE_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elif ENGINE_PLATFORM_MACOS
    #define GLFW_EXPOSE_NATIVE_COCOA
#endif

#include <GLFW/glfw3native.h>

#include <glm/glm.hpp>

#include <entt/entt.hpp>
