#pragma once

namespace __XXECS
{
    template<typename T>
    struct Color
    {
        T r, g, b, a;

        Color() = default;
        Color(T r, T g, T b, T a) : r(r), g(g), b(b), a(a) {}
        Color(T r, T g, T b) : r(r), g(g), b(b), a(1) {}

        operator T*() const
        {
            return reinterpret_cast<T*>(const_cast<Color*>(this));
        }
    };

    template<typename T>
    struct Position
    {
        T x, y, z, w;

        Position() = default;
        Position(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
        Position(T x, T y, T z) : x(x), y(y), z(z), w(1) {}

        operator T* () const
        {
            return reinterpret_cast<T*>(const_cast<Position*>(this));
        }
    };
}
