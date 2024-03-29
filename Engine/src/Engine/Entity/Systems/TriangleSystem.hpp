/*****************************************************************/ /**
 * \file   Triangle.hpp
 * \brief  Triangle component
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once
#include <Engine/Entity/ShapeSystem.hpp>
#include <Engine/Entity/Components/Color.hpp>
#include <Engine/Entity/Components/Drawable.hpp>
#include <Engine/Entity/Components/Position.hpp>
#include <Engine/Entity/Components/Triangle.hpp>

namespace XXECS::Entity
{
    class TriangleSystem : public ShapeSystem<TriangleSystem>
    {
    public:
        static auto Create(const entt::entity &entity) -> void
        {
            GetEntityManager().emplace<Color>(entity, Color(Math::Color(1, 0, 0)));
            GetEntityManager().emplace<Position>(entity, Position(Math::Position(0, 0)));
        }

        static auto RunParallel(const entt::entity &entity) -> void
        {
            auto &target = GetEntityManager().get<Drawable>(entity);
            const auto &source = GetEntityManager().get<Triangle>(entity);
            const auto &col = GetEntityManager().get<Color>(entity);
            const auto &pos = GetEntityManager().get<Position>(entity);

            target.vertices = {{source.points[0] + pos.position, col.color},
                               {source.points[1] + pos.position, col.color},
                               {source.points[2] + pos.position, col.color},};
        }
    };
}
