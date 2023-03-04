/*****************************************************************/ /**
 * \file   Circle.hpp
 * \brief  Circle component
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

#include <numbers>
#include <Engine/Entity/System.hpp>
#include <Engine/Entity/Components/Circle.hpp>
#include <Engine/Entity/Components/Color.hpp>
#include <Engine/Entity/Components/Drawable.hpp>
#include <Engine/Entity/Components/Position.hpp>

namespace __XXECS::Entity
{
    class CircleSystem : public System<CircleSystem>
    {
    public:
        static auto Create(const entt::entity entity) -> void
        {
            GetEntityManager().emplace<Color>(entity, Color(Math::Color(1, 0, 0)));
            GetEntityManager().emplace<Position>(entity, Position(Math::Position(0, 0)));
        }

        static auto Update(const entt::entity entity) -> void
        {
            auto &target = GetEntityManager().get<Drawable>(entity);
            const auto &source = GetEntityManager().get<Circle>(entity);
            const auto &col = GetEntityManager().get<Color>(entity);
            const auto &pos = GetEntityManager().get<Position>(entity);

            target.vertices[0] = {pos.position, col.color};

            for (auto i = 1; i < Circle::points; i++)
            {
                const double c = 2.0 * std::numbers::pi * static_cast<double>(i) / static_cast<double>(Circle::points -
                    1);
                target.vertices[i] = {
                    Math::Position(source.radius * static_cast<float>(std::cos(c)),
                                   source.radius * static_cast<float>(std::sin(c))) + pos.position,
                    col.color};
            }
        }
    };
}
