/*****************************************************************/ /**
 * \file   ShapeSystem.hpp
 * \brief  Shape System Base for entities
 * 
 * \author LD
 * \date   March 2023
 *********************************************************************/
#pragma once

#include <Engine/Entity/System.hpp>
#include <entt/entt.hpp>

namespace XXECS
{
    class Application;
}

namespace XXECS::Entity
{
    class EntityManager;

    template<typename Derived>
    struct ShapeSystem : System<Derived>
    {
        static auto Create(const entt::entity &arg) -> void
        {
        }

        static auto Delete(const entt::entity &arg) -> void
        {
        }
    };
}
