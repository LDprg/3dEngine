/*****************************************************************/ /**
 * \file   EntityManager.hpp
 * \brief  Entity Manager
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

#include <Engine/Entity/ShapeSystem.hpp>

#include "Engine/Entity/Components/Drawable.hpp"
#include "Engine/Math/Vertex.hpp"

#include <Engine/Entity/System.hpp>
#include <Engine/Entity/Systems/DynamicDrawableSystem.hpp>

#include <entt/entt.hpp>

namespace __XXECS::Entity
{
    class DrawableSystem;

    struct UpdateShapeTag
    {
    };

    struct DynamicShapeTag
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

    template<typename T> concept ShapeSystemConcept = requires() { std::derived_from<T, ShapeSystem<T>>; };
    template<typename T> concept SystemConcept = requires() { std::derived_from<T, System<T>>; };

    class EntityManager final : public entt::registry
    {
    public:
        template<ShapeComponentConcept Comp, ShapeSystemConcept Sys>
        constexpr auto CreateShape()
        {
            const auto entity = create();

            Create<Comp, Sys>(entity);
            Create<Drawable, DrawableSystem>(entity, Drawable(Comp::vertices, Comp::indices));

            emplace<UpdateShapeTag>(entity);

            return entity;
        }

        template<ShapeComponentConcept Comp, ShapeSystemConcept Sys>
        constexpr auto CreateDynamicShape()
        {
            const auto entity = create();

            Create<Comp, Sys>(entity);
            Create<Drawable, DynamicDrawableSystem>(entity, Drawable(Comp::vertices, Comp::indices));

            emplace<DynamicShapeTag>(entity);

            return entity;
        }

        template<ShapeComponentConcept Comp, SystemConcept Sys, typename... Other, typename... Args>
        constexpr auto UpdateShape(Args &&... args)
        {
            const auto v = view<Comp, Other..., Drawable, UpdateShapeTag>(std::forward<Args>(args)...);

            Sys::Execute(v);

            DrawableSystem::Update(v);

            remove<UpdateShapeTag>(v.begin(), v.end());

            return v;
        }

        template<ShapeComponentConcept Comp, SystemConcept Sys, typename... Other, typename... Args>
        constexpr auto UpdateDynamicShape(Args &&... args)
        {
            const auto v = view<Comp, Other..., Drawable, DynamicShapeTag>(std::forward<Args>(args)...);

            Sys::Execute(v);

            DynamicDrawableSystem::Update(v);

            return v;
        }

        template<typename... Other, typename... Args>
        constexpr auto DrawShape(Args &&... args)
        {
            const auto v = view<Other..., Drawable>(entt::exclude<DynamicShapeTag>, std::forward<Args>(args)...);

            DrawableSystem::Execute(v);

            return v;
        }

        template<typename... Other, typename... Args>
        constexpr auto DrawDynamicShape(Args &&... args)
        {
            const auto v = view<Other..., Drawable, DynamicShapeTag>(std::forward<Args>(args)...);

            DynamicDrawableSystem::Execute(v);

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
