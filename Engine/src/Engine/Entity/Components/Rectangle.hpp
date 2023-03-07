/*****************************************************************/ /**
 * \file   Rectangle.hpp
 * \brief  Rectangle component
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once
#include <Engine/Entity/Components/Drawable.hpp>
#include <Engine/Math/Vertex.hpp>

namespace XXECS::Entity
{
    struct Rectangle
    {
        inline static const Math::Indices indices = {0, 1, 2, 2, 3, 0};
        inline static const Math::Vertices vertices = 4;

        float width = 1;
        float height = 1;
    };
}
