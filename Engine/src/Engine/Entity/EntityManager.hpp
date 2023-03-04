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
        template<ShapeComponentConcept Comp, ShapeSystemConcept Sys>
        constexpr auto CreateShape()
        {
            const auto entity = create();
            auto &shape = Create<Comp, Sys>(entity);
            auto &draw = Create<Drawable, DrawableSystem>(entity, Drawable(Comp::vertices, Comp::indices));

            emplace<UpdateShapeTag>(entity);
            return std::tie(entity, shape, draw);
        }

        template<ShapeComponentConcept Comp, ShapeSystemConcept Sys>
        constexpr auto CreateDynamicShape()
        {
            const auto entity = create();
            auto &shape = Create<Comp, Sys>(entity);
            auto &draw = Create<Drawable, DrawableSystem>(entity, Drawable(Comp::vertices, Comp::indices));

            return std::tie(entity, shape, draw);
        }

        template<ShapeComponentConcept Comp, ShapeSystemConcept Sys, typename... Other, typename... Args>
        constexpr auto UpdateShape(Args &&... args)
        {
            const auto v = view<Comp, Other..., Drawable, UpdateShapeTag>(std::forward<Args>(args)...);

            for (auto entity : v)
            {
                Sys::Update(entity);
                remove<UpdateShapeTag>(entity);
            }

            return v;
        }

        template<ShapeComponentConcept Comp, ShapeSystemConcept Sys, typename... Other, typename... Args>
        constexpr auto UpdateDynamicShape(Args &&... args)
        {
            const auto v = view<Comp, Other..., Drawable>(std::forward<Args>(args)...);

            for (auto entity : v)
                Sys::Update(entity);

            return v;
        }

        template<typename... Other, typename... Args>
        constexpr auto DrawShape(Args &&... args)
        {
            const auto v = view<Other..., Drawable>(std::forward<Args>(args)...);

            for (auto entity : v)
                DrawableSystem::Update(entity);

            return v;
        }

        template<ShapeComponentConcept Comp, ShapeSystemConcept Sys, typename... Args>
        constexpr auto Create(const entt::entity &entt, Args &&... args) -> decltype(auto)
        {
            auto &item = entt::registry::emplace<Comp>(entt, std::forward<Args>(args)...);
            Sys::Create(entt);
            return item;
        }

        template<ShapeComponentConcept Comp, ShapeSystemConcept Sys>
        constexpr auto Remove(const entt::entity &entt)
        {
            auto &item = entt::registry::remove<Comp>(entt);
            Sys::Delete(entt);
            return item;
        }
    };
}
