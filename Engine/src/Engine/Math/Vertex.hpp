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

    typedef std::initializer_list<Index> FixedIndices;
    typedef std::initializer_list<Vertex> FixedVertices;

	typedef Size IndicesSize;
    typedef Size VerticesSize;

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

        Buffer(const std::initializer_list<T>& iList) : Buffer(static_cast<Size>(iList.size()))
        {
            std::copy(iList.begin(), iList.end(), data.get());
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
