/*****************************************************************/ /**
 * \file   EntityManager.hpp
 * \brief  Entity Manager
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

#include  "Engine/Entity/System.hpp"
#include "Engine/Entity/Components/Drawable.hpp"
#include "Engine/Math/Vertex.hpp"

#include <entt/entt.hpp>

namespace __XXECS::Entity
{
    class DrawableSystem;

    struct UpdateShapeTag
    {
    };

    template<typename T> concept ShapeComponentConcept = requires()
    {
        {
            T::vertices
        } -> std::convertible_to<Math::Vertices>; {
            T::indices
        } -> std::convertible_to<Math::Indices>;
    };

    template<typename T> concept ShapeSystemConcept = requires() { std::derived_from<T, System<T>>; };

    class EntityManager final : public entt::registry
    {
    public:
        template<ShapeComponentConcept T>
        constexpr auto CreateShape()
        {
            const auto entity = create();
            auto &shape = emplace<T>(entity);
            auto &draw = emplace<Drawable, DrawableSystem>(entity, Drawable(T::vertices, T::indices));

            emplace<UpdateShapeTag>(entity);
            return std::tie(entity, shape, draw);
        }

        template<ShapeComponentConcept T>
        constexpr auto CreateDynamicShape()
        {
            const auto entity = create();
            auto &shape = emplace<T>(entity);
            auto &draw = emplace<Drawable, DrawableSystem>(entity, Drawable(T::vertices, T::indices));

            return std::tie(entity, shape, draw);
        }

        template<ShapeComponentConcept Comp, ShapeSystemConcept Sys, typename... Other, typename... Args>
        constexpr auto UpdateShape(Args &&... args)
        {
            const auto v = view<Comp, Other..., Drawable, UpdateShapeTag>(std::forward<Args>(args)...);

            v.each([this](const auto entity, auto &shape, auto &draw)
            {
                Sys::Update(shape, draw);
                remove<UpdateShapeTag>(entity);
            });

            return v;
        }

        template<ShapeComponentConcept Comp, ShapeSystemConcept Sys, typename... Other, typename... Args>
        constexpr auto UpdateDynamicShape(Args &&... args)
        {
            const auto v = view<Comp, Other..., Drawable>(std::forward<Args>(args)...);

            v.each([this](const auto entity, auto &shape, auto &draw)
            {
                Sys::Update(shape, draw);
            });

            return v;
        }

        template<typename... Other, typename... Args>
        constexpr auto DrawShape(Args &&... args)
        {
            const auto v = view<Other..., Drawable>(std::forward<Args>(args)...);

            for (auto entity : v)
                DrawableSystem::Update(get<Drawable>(entity));

            return v;
        }

        template<typename Type, typename... Args>
        constexpr auto emplace(const entt::entity &entt, Args &&... args) -> decltype(auto)
        {
            return entt::registry::emplace<Type>(entt, std::forward<Args>(args)...);
        }

        template<ShapeComponentConcept Comp, ShapeSystemConcept Sys, typename... Args>
        constexpr auto emplace(const entt::entity &entt, Args &&... args) -> decltype(auto)
        {
            auto &item = entt::registry::emplace<Comp>(entt, std::forward<Args>(args)...);
            Sys::Create(item);
            return item;
        }

        template<typename Type>
        constexpr auto remove(const entt::entity &entt)
        {
            return entt::registry::remove<Type>(entt);
        }

        template<ShapeComponentConcept Comp, ShapeSystemConcept Sys>
        constexpr auto remove(const entt::entity &entt)
        {
            auto &item = entt::registry::remove<Comp>(entt);
            Sys::Delete(item);
            return item;
        }
    };
}
