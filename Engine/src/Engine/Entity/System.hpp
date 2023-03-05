/*****************************************************************/ /**
 * \file   System.hpp
 * \brief  System Base for entities
 * 
 * \author LD
 * \date   March 2023
 *********************************************************************/
#pragma once

#include <entt/entt.hpp>

namespace __XXECS
{
    class Application;
}

namespace __XXECS::Entity
{
    class EntityManager;

    template<typename Derived>
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

        static auto GetEntityManager() -> EntityManager&
        {
            return Application::Get()->GetEntityManager();
        }
    };
}
