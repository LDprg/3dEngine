/*****************************************************************/ /**
 * \file   Vertex.hpp
 * \brief  Vertices and indices type definitions
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

#include "Engine/Math/General.hpp"
#include "Engine/Math/Vector.hpp"

namespace __XXECS::Math
{
    template<typename T>
    struct Buffer;

    typedef Diligent::Uint32 Index;

    struct Vertex
    {
        Position pos;
        Color color;
    };

	typedef Buffer<Vertex> Vertices;
    typedef Buffer<Index> Indices;

	template<typename T>
    struct Buffer
    {
        std::shared_ptr<T[]> data;

        Buffer(const Size &size)
            : data(new T[size]), m_size(size)
        {
        }

        Buffer(const std::initializer_list<T>& iList) : Buffer(iList.size())
        {
            std::copy(iList.begin(), iList.end(), data.get());
        }

		template<T... vals>
        Buffer(const std::integer_sequence<T, vals...>) : Buffer(std::initializer_list<T>{vals...})
        {            
        }

        operator T *() const
        {
            return data.get();
        }

        [[nodiscard]] auto SizeInBytes() const -> Size
        {
            return sizeof(T) * m_size;
        }

        [[nodiscard]] auto size() const -> Size
        {
            return m_size;
        }

    private:
        Size m_size;
    };
}
