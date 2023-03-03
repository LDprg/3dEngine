/*****************************************************************/ /**
 * \file   RectangleSystem.hpp
 * \brief  Rectangle System
 * 
 * \author LD
 * \date   March 2023
 *********************************************************************/
#pragma once
#include <Engine/Entity/System.hpp>
#include <Engine/Entity/Components/Drawable.hpp>
#include <Engine/Entity/Components/Rectangle.hpp>
#include <Engine/Entity/Extenders/Renderable.hpp>
#include <Engine/Math/Vertex.hpp>

namespace __XXECS::Entity
{
    class RectangleSystem : System<RectangleSystem>
    {
    public:
        static auto Update(const Rectangle &source, Drawable &target) -> void
        {
            const float width = std::max(source.width, 0.f);
            const float height = std::max(source.height, 0.f);
            const float nwidth = std::min(source.width, 0.f);
            const float nheight = std::min(source.height, 0.f);

            target.vertices = {{Math::Position(width, height) + source.position, source.color},
                               {Math::Position(width, nheight) + source.position, source.color},
                               {Math::Position(nwidth, nheight) + source.position, source.color},
                               {Math::Position(nwidth, height) + source.position, source.color},};
        }
    };
}
