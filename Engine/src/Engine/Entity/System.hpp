/*****************************************************************/ /**
 * \file   EntityManager.hpp
 * \brief  Entity Manager
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

#include <entt/entt.hpp>

namespace __XXECS::Entity
{
    template<class Derived>
    struct System
    {
        static auto Create(const entt::entity arg) -> void
        {
        }

        static auto Update(const entt::entity arg) -> void
        {
        }

        static auto Delete(const entt::entity arg) -> void
        {
        }
    };
}
