/*****************************************************************/ /**
 * \file   EntityManager.hpp
 * \brief  Entity Manager
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once
#include <entt/entt.hpp>

namespace __XXECS
{
    class EntityManager : public entt::registry
    {
    public:
        EntityManager() = default;
        virtual ~EntityManager() = default;
    };
}
