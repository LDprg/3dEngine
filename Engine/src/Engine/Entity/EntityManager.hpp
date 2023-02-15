/*****************************************************************/ /**
 * \file   EntityManager.hpp
 * \brief  Entity Manager
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
// ReSharper disable CppInconsistentNaming
#pragma once

#include "Engine/Entity/Components/Drawable.hpp"
#include "Engine/Math/Vertex.hpp"

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

	template<typename T> concept UpdateAbleConcept = requires(const T &arg, Drawable &target)
    {
        T::Update(arg, target);
    };

    template<typename T> concept ShapeComponentConcept = requires(T)
    {
        {
            T::vertices
        } -> std::convertible_to<Math::Vertices>; {
            T::indices
        } -> std::convertible_to<Math::Indices>;
    };

    template<typename T> concept ShapeComponentUpdateAbleConcept = ShapeComponentConcept<T> && UpdateAbleConcept<T>;

    class EntityManager final : public entt::registry
    {
    public:
        template<ShapeComponentConcept T>
        auto CreateShape()
        {
            const auto entity = create();
            auto &shape = emplace<T>(entity);
            auto &draw = emplace<Drawable>(entity, Drawable(T::vertices, T::indices));
            return std::tie(entity, shape, draw);
        }

		template<ShapeComponentUpdateAbleConcept T>
        auto UpdateShape() -> auto&
        {
            const auto v = view<T, Drawable>();

            v.each([this](auto &shape, auto &draw) { T::Update(shape, draw); });

			return v;
        }

        template<typename Type, typename... Args>
        auto emplace(const entt::entity &entt, Args &&... args) -> auto&
        {
            return entt::registry::emplace<Type>(entt, std::forward<Args>(args)...);
        }

        template<CreateAbleConcept Type, typename... Args>
        auto emplace(const entt::entity &entt, Args &&... args) -> auto&
        {
            auto &item = entt::registry::emplace<Type>(entt, std::forward<Args>(args)...);
            Type::Create(item);
            return item;
        }

        template<typename Type>
        auto remove(const entt::entity &entt)
        {
            return entt::registry::remove<Type>(entt);
        }

        template<DeleteAbleConcept Type>
        auto remove(const entt::entity &entt)
        {
            auto &item = entt::registry::remove<Type>(entt);
            Type::Delete(item);
            return item;
        }
    };
}
