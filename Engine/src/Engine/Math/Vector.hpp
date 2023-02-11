#pragma once

namespace __XXECS
{
    template<typename T>
    struct Color
    {
        T r, g, b, a;

        operator T*() const
        {
            return reinterpret_cast<T*>(const_cast<Color*>(this));
        }
    };
}
