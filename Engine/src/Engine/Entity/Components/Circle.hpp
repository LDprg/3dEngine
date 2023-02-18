/*****************************************************************/ /**
 * \file   Circle.hpp
 * \brief  Circle component
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

#include <numbers>

namespace __XXECS::Entity
{
    template<Math::Index N, Math::Index... Next>
    struct CircleSequenceHelper : CircleSequenceHelper<N - 1, 0, N + 1, N, Next...>
        { };

    template<Math::Index... Next>
        struct CircleSequenceHelper<0, Next...>
        { using Type = std::integer_sequence<Math::Index, Next ... >; };

    template<Math::Index N>
    using MakeCircleSequence = typename CircleSequenceHelper<N-1, 0, 1, N>::Type;
	
	template<int Points>
    struct GenericCircle
    {
        static_assert(Points > 1, "The circle minimum resolution is 2");

		inline static constexpr int points = Points + 1;
        inline static const Math::Indices indices = MakeCircleSequence<Points>();
        inline static const Math::Vertices vertices = points;

		float radius = 0.25;
        Math::Color color{1, 0, 0};

        static auto Update(const GenericCircle &source, Drawable &target) -> void
        {
            target.vertices[0] = {Math::Position(0,0), source.color};

            for (int i = 1; i < points; i++)
            {
                const double c = 2.0 * std::numbers::pi * static_cast<double>(i) / static_cast<double>(Points);
                target.vertices[i] = {
                    Math::Position(source.radius * static_cast<float>(std::cos(c)),
                                                     source.radius * static_cast<float>(std::sin(c))),
                                      source.color};
            }
        }
    };

	using Circle = GenericCircle<32>;
}
