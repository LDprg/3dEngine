/*****************************************************************/ /**
 * \file   EntityManager.hpp
 * \brief  Entity Manager
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

#include "Engine/Entity/Components/Drawable.hpp"
#include "Engine/Math/Vertex.hpp"

#include <entt/entt.hpp>

namespace __XXECS::Entity
{
    template<class Derived>
    class System
    {
        static constexpr bool has_Create = requires() { Derived::Create(); };
        static constexpr bool has_Update = requires() { Derived::Update(); };
        static constexpr bool has_Delete = requires() { Derived::Delete(); };

    public:
        template<typename T, typename Arg>
        static auto Create(Arg &&arg) -> std::shared_ptr<T>
        {
            if constexpr (has_Create)
                return std::shared_ptr<T>(Derived::Create(std::forward<Arg>(arg)));
        }

        template<typename T, typename Arg>
        static auto Update(Arg &&arg) -> std::shared_ptr<T>
        {
            if constexpr (has_Update)
                return std::shared_ptr<T>(Derived::Update(std::forward<Arg>(arg)));
        }

        template<typename T, typename Arg>
        static auto Delete(Arg &&arg) -> std::shared_ptr<T>
        {
            if constexpr (has_Delete)
                return std::shared_ptr<T>(Derived::Delete(std::forward<Arg>(arg)));
        }
    };
}
