/*****************************************************************/ /**
 * \file   Circle.hpp
 * \brief  Circle component
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

#include <numbers>
#include <Engine/Entity/System.hpp>
#include <Engine/Entity/Components/Circle.hpp>
#include <Engine/Entity/Components/Drawable.hpp>
#include <Engine/Entity/Extenders/Renderable.hpp>

namespace __XXECS::Entity
{
    class CircleSystem : System<CircleSystem>
    {
    public:
        static auto Update(const Circle &source, Drawable &target) -> void
        {
            target.vertices[0] = {source.position, source.color};

            for (auto i = 1; i < Circle::points; i++)
            {
                const double c = 2.0 * std::numbers::pi * static_cast<double>(i) / static_cast<double>(Circle::points -
                    1);
                target.vertices[i] = {
                    Math::Position(source.radius * static_cast<float>(std::cos(c)),
                                   source.radius * static_cast<float>(std::sin(c))) + source.position,
                    source.color};
            }
        }
    };
}
