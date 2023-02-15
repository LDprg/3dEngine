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
    template<typename T> concept CreateAbleConcept = requires(T &arg)
    {
        T::Create(arg);
    };

    template<typename T> concept DeleteAbleConcept = requires(T &arg)
    {
        T::Delete(arg);
    };

    class EntityManager final
    {
    public:
        EntityManager() = default;
        ~EntityManager() = default;

        auto GetNative() -> entt::registry&
        {
            return m_registry;
        }

        auto CreateEntity() -> entt::entity
        {
            return m_registry.create();
        }

        auto DestroyEntity(const entt::entity entity) -> void
        {
            m_registry.destroy(entity);
        }

        template<typename Type, typename... Args>
        auto AddComponent(const entt::entity &entt, Args &&... args) -> auto&
        {
            return m_registry.emplace<Type>(entt, std::forward<Args>(args)...);
        }

        template<CreateAbleConcept Type, typename... Args>
        auto AddComponent(const entt::entity &entt, Args &&... args) -> auto&
        {
            auto &item = m_registry.emplace<Type>(entt, std::forward<Args>(args)...);
            Type::Create(item);
            return item;
        }

        template<typename Type>
        auto RemoveComponent(const entt::entity &entt) 
        {
            return m_registry.remove<Type>(entt);
        }

        template<DeleteAbleConcept Type>
        auto RemoveComponent(const entt::entity &entt) 
        {
            auto &item = m_registry.remove<Type>(entt);
            Type::Delete(item);
            return item;
        }

        template<typename Type, typename... Exclude>
        auto GetEntities(entt::exclude_t<Exclude...>  = {}) -> auto
        {
            return m_registry.view<Type>(entt::exclude_t<Exclude...>{});
        }

    private:
        entt::registry m_registry;
    };
}
