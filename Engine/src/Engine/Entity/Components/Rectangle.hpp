/*****************************************************************/ /**
 * \file   Rectangle.hpp
 * \brief  Rectangle component
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once
#include <Engine/Entity/Components/Drawable.hpp>
#include <Engine/Entity/Extenders/Renderable.hpp>
#include <Engine/Math/Vertex.hpp>

namespace __XXECS::Entity
{
    struct Rectangle : Position<Math::Position(0, 0)>, Color<Math::Color(1, 0, 0)>
    {
        inline static const Math::Indices indices = {0, 1, 2, 2, 3, 0};
        inline static const Math::Vertices vertices = 4;

        float width = 1;
        float height = 1;
    };
}
