/*****************************************************************/ /**
 * \file   Triangle.hpp
 * \brief  Triangle component
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

namespace XXECS::Entity
{
    struct Triangle
    {
        inline static const Math::Indices indices = {0, 1, 2};
        inline static const Math::Vertices vertices = 3;

        Math::Position points[3]{Math::Position(-0.5, -0.5), Math::Position(0.0, +0.5), Math::Position(+0.5, -0.5)};
    };
}
