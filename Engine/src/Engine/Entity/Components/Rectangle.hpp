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
			const float width = std::max(source.width, 0.f);
			const float height = std::max(source.height, 0.f);
            const float nwidth = std::min(source.width, 0.f);
            const float nheight = std::min(source.height, 0.f);

            target.vertices = {
                {Math::Position(width, height), source.color},
                {Math::Position(width, nheight), source.color},
                {Math::Position(nwidth, nheight), source.color},
                {Math::Position(nwidth, height), source.color},
            };
        }
    };
}
