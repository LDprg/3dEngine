/*****************************************************************/ /**
 * \file   Vector.hpp
 * \brief  Common vector types
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

namespace __XXECS
{
    struct Color
    {
        float r, g, b, a;

        Color() = default;

        Color(const float r, const float g, const float b, const float a)
            : r(r), g(g), b(b), a(a)
        {
        }

        Color(const float r, const float g, const float b)
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

        Position() = default;

        Position(const float x, const float y, const float z, const float w)
            : x(x), y(y), z(z), w(w)
        {
        }

        Position(const float x, const float y, const float z)
            : x(x), y(y), z(z), w(1.f)
        {
        }

        Position(const float x, const float y)
            : x(x), y(y), z(0.f), w(1.f)
        {
        }

        operator float *() const
        {
            return reinterpret_cast<float *>(const_cast<Position *>(this));
        }
    };
}
