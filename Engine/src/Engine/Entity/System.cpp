/*****************************************************************/ /**
 * \file   System.cpp
 * \brief  System struct implementation
 * 
 * \author LD
 * \date   March 2023
 *********************************************************************/
#pragma once

#include <Engine/Core/Application.hpp>
#include <Engine/Entity/System.hpp>

using namespace __XXECS::Entity;

template<typename Derived>
auto System<Derived>::GetEntityManager() -> EntityManager&
{
    return Application::Get()->GetEntityManager();
}
