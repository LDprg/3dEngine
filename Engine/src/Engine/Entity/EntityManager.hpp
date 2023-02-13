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
