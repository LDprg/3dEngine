#pragma once

namespace __XXECS
{
    struct Color
    {
        float r, g, b, a;

        Color() = default;
        Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
        Color(float r, float g, float b) : r(r), g(g), b(b), a(1.f) {}

        operator float*() const
        {
            return reinterpret_cast<float*>(const_cast<Color*>(this));
        }
    };
    
    struct Position
    {
        float x, y, z, w;

        Position() = default;
        Position(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
        Position(float x, float y, float z) : x(x), y(y), z(z), w(1.f) {}
        Position(float x, float y) : x(x), y(y), z(0.f), w(1.f) {}

        operator float*() const
        {
            return reinterpret_cast<float*>(const_cast<Position*>(this));
        }
    };
}
