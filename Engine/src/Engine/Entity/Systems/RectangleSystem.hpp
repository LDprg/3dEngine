/*****************************************************************/ /**
 * \file   RectangleSystem.hpp
 * \brief  Rectangle System
 * 
 * \author LD
 * \date   March 2023
 *********************************************************************/
#pragma once
#include <Engine/Entity/ShapeSystem.hpp>
#include <Engine/Entity/Components/Color.hpp>
#include <Engine/Entity/Components/Drawable.hpp>
#include <Engine/Entity/Components/Position.hpp>
#include <Engine/Entity/Components/Rectangle.hpp>
#include <Engine/Math/Vertex.hpp>

namespace XXECS::Entity
{
    class RectangleSystem : public ShapeSystem<RectangleSystem>
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
            const auto &source = GetEntityManager().get<Rectangle>(entity);
            const auto &col = GetEntityManager().get<Color>(entity);
            const auto &pos = GetEntityManager().get<Position>(entity);

            const float width = std::max(source.width, 0.f);
            const float height = std::max(source.height, 0.f);
            const float nwidth = std::min(source.width, 0.f);
            const float nheight = std::min(source.height, 0.f);

            target.vertices = {{Math::Position(width, height) + pos.position, col.color},
                               {Math::Position(width, nheight) + pos.position, col.color},
                               {Math::Position(nwidth, nheight) + pos.position, col.color},
                               {Math::Position(nwidth, height) + pos.position, col.color},};
        }
    };
}
