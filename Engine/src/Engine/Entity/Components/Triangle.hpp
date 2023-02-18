/*****************************************************************/ /**
 * \file   Triangle.hpp
 * \brief  Triangle component
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

namespace __XXECS::Entity
{
    struct Triangle
    {
        inline static const Math::Indices indices = {0,1,2};
        inline static const Math::Vertices vertices = 3;

        Math::Position position[3]{ Math::Position(-0.5, -0.5),
                                    Math::Position(0.0, +0.5),
                                    Math::Position(+0.5, -0.5)};
        Math::Color color{1, 0, 0};

        static auto Update(const Triangle &source, Drawable &target) -> void
        {
            target.vertices = {{source.position[0], source.color}, {source.position[1], source.color},
                               {source.position[2], source.color},};
        }
    };
}
