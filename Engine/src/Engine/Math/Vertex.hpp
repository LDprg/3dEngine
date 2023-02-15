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

    struct Vertices
    {
        std::shared_ptr<Vertex[]> data;

        Vertices(const Size &size)
            : data(new Vertex[size]), m_size(size)
        {
        }

        Vertices(const std::initializer_list<Vertex> iList)
            : Vertices(static_cast<Size>(iList.size()))
        {
            std::copy(iList.begin(), iList.end(), data.get());
        }

        operator Vertex *() const
        {
            return data.get();
        }

        [[nodiscard]] auto SizeInBytes() const -> Size
        {
            return sizeof(Vertex) * m_size;
        }

        [[nodiscard]] auto size() const -> Size
        {
            return m_size;
        }

    private:
        Size m_size;
    };

    struct Indices
    {
        std::shared_ptr<Index[]> data;

        Indices(const Size size)
            : data(new Index[size]), m_size(size)
        {
        }

        Indices(const std::initializer_list<Index> iList)
            : Indices(static_cast<Size>(iList.size()))
        {
            std::copy(iList.begin(), iList.end(), data.get());
        }

        operator Index *() const
        {
            return data.get();
        }

        [[nodiscard]] auto SizeInBytes() const -> Size
        {
            return sizeof(Index) * m_size;
        }

        [[nodiscard]] auto size() const -> Size
        {
            return m_size;
        }

    private:
        Size m_size;
    };
}
