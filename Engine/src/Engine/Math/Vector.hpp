/*****************************************************************/ /**
 * \file   Vector.hpp
 * \brief  Common vector types
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

namespace XXECS::Math
{
    struct Color
    {
        float r, g, b, a;

        constexpr Color() = default;

        constexpr Color(const float r, const float g, const float b, const float a)
            : r(r), g(g), b(b), a(a)
        {
        }

        constexpr Color(const float r, const float g, const float b)
            : r(r), g(g), b(b), a(1.f)
        {
        }

        operator float *() const
        {
            return reinterpret_cast<float *>(const_cast<Color *>(this));
        }
    };

    struct Position
    {
        float x, y, z, w;

        constexpr Position() = default;

        constexpr Position(const float x, const float y, const float z, const float w)
            : x(x), y(y), z(z), w(w)
        {
        }

        constexpr Position(const float x, const float y, const float z)
            : x(x), y(y), z(z), w(1.f)
        {
        }

        constexpr Position(const float x, const float y)
            : x(x), y(y), z(0.f), w(1.f)
        {
        }

        auto operator +(const Position &other) const -> Position
        {
            return Position(x + other.x, y + other.y, z + other.z, w);
        }

        auto operator -(const Position &other) const -> Position
        {
            return Position(x - other.x, y - other.y, z - other.z, w);
        }

        operator float *() const
        {
            return reinterpret_cast<float *>(const_cast<Position *>(this));
        }
    };
}
