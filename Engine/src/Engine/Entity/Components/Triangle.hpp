/*****************************************************************/ /**
 * \file   Triangle.hpp
 * \brief  Triangle component
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once
#include <Engine/Entity/Extenders/Renderable.hpp>

namespace __XXECS::Entity
{
    struct Triangle : Position<Math::Position(0, 0)>, Color<Math::Color(1, 0, 0)>
    {
        inline static const Math::Indices indices = {0, 1, 2};
        inline static const Math::Vertices vertices = 3;

        Math::Position points[3]{Math::Position(-0.5, -0.5), Math::Position(0.0, +0.5), Math::Position(+0.5, -0.5)};

        static auto Update(const Triangle &source, Drawable &target) -> void
        {
            target.vertices = {{source.points[0] + source.position, source.color},
                               {source.points[1] + source.position, source.color},
                               {source.points[2] + source.position, source.color},};
        }
    };
}
