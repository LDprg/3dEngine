/*****************************************************************/ /**
 * \file   Renderable.hpp
 * \brief  Renderable extenders
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once
#include <Engine/Math/Vector.hpp>
#include <Engine/Math/Vertex.hpp>

namespace __XXECS::Entity
{
    template<Math::Color Col>
    struct Color
    {
        Math::Color color = Col;
    };

    template<Math::Position Pos>
    struct Position
    {
        Math::Position position = Pos;
    };
}
