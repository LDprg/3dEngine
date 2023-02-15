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

namespace __XXECS::Entity
{
    struct Rectangle
    {
        inline static constexpr Math::FixedIndices indices{0, 1, 2, 2, 3, 0};
        inline static constexpr Math::VerticesSize vertices = 4;

        float width = 1;
        float height = 1;
        Math::Color color{1, 0, 0};

        static auto Update(const Rectangle &source, Drawable &target) -> void
        {
            target.vertices = {{Math::Position(source.width, source.height), source.color},
                               {Math::Position(source.width, 0), source.color}, {Math::Position(0, 0), source.color},
                               {Math::Position(0, source.height), source.color},};
        }
    };
}
