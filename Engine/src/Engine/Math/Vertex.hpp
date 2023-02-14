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

namespace __XXECS
{
    typedef Diligent::Uint32 Index;

    struct Vertex
    {
        Position pos;
        Color color;
    };

    struct Vertices
    {
        std::shared_ptr<Vertex[]> data;

        explicit Vertices(const Size size)
            : m_size(size)
        {
            data = std::make_shared<Vertex[]>(size);
        }

        Vertices(const std::initializer_list<Vertex> iList)
            : Vertices(static_cast<Size>(iList.size()))
        {
            std::ranges::copy(iList.begin(), iList.end(), data.get());
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

        explicit Indices(const Size size)
            : m_size(size)
        {
            data = std::make_shared<Index[]>(size);
        }

        Indices(const std::initializer_list<Index> iList)
            : Indices(static_cast<Size>(iList.size()))
        {
            std::ranges::copy(iList.begin(), iList.end(), data.get());
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
