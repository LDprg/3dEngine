/*****************************************************************/ /**
 * \file   Circle.hpp
 * \brief  Circle component
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

namespace __XXECS::Entity
{
	template<int Points>
    struct Circle
    {
        inline static const Math::Indices indices = std::make_integer_sequence<Math::Index, Points>();
        inline static const Math::Vertices vertices = Points;

		int radius = 10;
        Math::Color color{1, 0, 0};

        static auto Update(const Circle &source, Drawable &target) -> void
        {
            
        }
    };
}
