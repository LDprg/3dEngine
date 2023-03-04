/*****************************************************************/ /**
 * \file   Engine.hpp
 * \brief  Include all of the Engine header
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

#include "Engine/Core/Application.hpp"
#include "Engine/Core/EntryPoint.hpp"
#include "Engine/Core/Log.hpp"

#include "Engine/Events/Event.hpp"
#include "Engine/Events/Input.hpp"
#include "Engine/Events/Key.hpp"

#include "Engine/Renderer/imgui.hpp"
#include "Engine/Renderer/Renderer.hpp"

#include "Engine/Math/Vertex.hpp"

#include "Engine/Entity/Systems/DrawableSystem.hpp"
#include "Engine/Entity/Systems/TriangleSystem.hpp"
#include "Engine/Entity/Systems/RectangleSystem.hpp"
#include "Engine/Entity/Systems/CircleSystem.hpp"

#include "Engine/Entity/Components/Drawable.hpp"
#include "Engine/Entity/Components/Triangle.hpp"
#include "Engine/Entity/Components/Rectangle.hpp"
#include "Engine/Entity/Components/Circle.hpp"


#include <any>

using namespace __XXECS;
