/*****************************************************************/ /**
 * \file   Triangle.hpp
 * \brief  Triangle component
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once
#include <Engine/Entity/System.hpp>
#include <Engine/Entity/Components/Drawable.hpp>
#include <Engine/Entity/Components/Triangle.hpp>
#include <Engine/Entity/Extenders/Renderable.hpp>

namespace __XXECS::Entity
{
    class TriangleSystem : System<TriangleSystem>
    {
    public:
        static auto Update(const Triangle &source, Drawable &target) -> void
        {
            target.vertices = {{source.points[0] + source.position, source.color},
                               {source.points[1] + source.position, source.color},
                               {source.points[2] + source.position, source.color},};
        }
    };
}
