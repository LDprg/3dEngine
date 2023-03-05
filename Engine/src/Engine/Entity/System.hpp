/*****************************************************************/ /**
 * \file   System.hpp
 * \brief  System Base for entities
 * 
 * \author LD
 * \date   March 2023
 *********************************************************************/
#pragma once

#include <execution>
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
        template<typename T>
        static auto Execute(T& v) -> void
        {
            if constexpr (requires(Derived) { Derived::Run(entt::entity{}); })
                for (auto &entity : v)
                    Derived::Run(entity);
            else if constexpr (requires(Derived) { Derived::RunParallel(entt::entity{}); })
                std::for_each(std::execution::par_unseq, v.begin(), v.end(), [](auto &&entity)
                {
                    Derived::RunParallel(std::forward<const entt::entity>(entity));
                });
        }

        static auto GetEntityManager() -> EntityManager&
        {
            return Application::Get()->GetEntityManager();
        }
    };
}
