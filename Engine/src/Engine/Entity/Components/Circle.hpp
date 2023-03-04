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
    {
    };

    template<Math::Index... Next>
    struct CircleSequenceHelper<0, Next...>
    {
        typedef std::integer_sequence<Math::Index, Next...> Type;
    };

    template<Math::Index N>
    using MakeCircleSequence = typename CircleSequenceHelper<N - 1, 0, 1, N>::Type;

    template<int Points>
    struct GenericCircle
    {
        static_assert(Points > 1, "The circle minimum resolution is 2");

        inline static constexpr int points = Points + 1;
        inline static const Math::Indices indices = MakeCircleSequence<Points>();
        inline static const Math::Vertices vertices = points;

        float radius = 0.25;
    };

    typedef GenericCircle<32> Circle;
}
