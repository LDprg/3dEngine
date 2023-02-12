#pragma once

#include <initializer_list>
#include <vector>

#include <BasicTypes.h>

#include "Vector.hpp"
#include "Engine/Core/Log.h"

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
		Vertex* data;

		Vertices(size_t size)
			:m_size(size)
		{
			data = new Vertex[size];
		}

		Vertices(std::initializer_list<Vertex> iList)
			:Vertices(iList.size())
		{
			std::ranges::copy(iList.begin(), iList.end(), data);
		}
		
		operator Vertex* () const
		{
			return data;
		}

		[[nodiscard]] size_t sizeInBytes() const
		{
			return sizeof(Vertex) * m_size;
		}

		[[nodiscard]] size_t size() const
		{
			return m_size;
		}

	private:
		size_t m_size;
	};

	struct Indices
	{
		Index* data;

		Indices(size_t size)
			:m_size(size)
		{
			data = new Index[size];
		}

		Indices(std::initializer_list<Index> iList)
			:Indices(iList.size())
		{
			std::copy(iList.begin(), iList.end(), data);
		}

		operator Index* () const
		{
			return data;
		}

		[[nodiscard]] size_t sizeInBytes() const
		{
			return sizeof(Index) * m_size;
		}

		[[nodiscard]]  size_t size() const
		{
			return m_size;
		}

	private:
		size_t m_size;
	};
}
