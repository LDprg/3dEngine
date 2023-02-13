#pragma once

#include <initializer_list>
#include <memory>

#include <BasicTypes.h>

#include "Vector.hpp"
#include "Engine/Core/Log.h"
#include "Engine/Math/General.hpp"

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

		operator Vertex*() const
		{
			return data.get();
		}

		[[nodiscard]] Size SizeInBytes() const
		{
			return sizeof(Vertex) * m_size;
		}

		[[nodiscard]] Size size() const
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

		operator Index*() const
		{
			return data.get();
		}

		[[nodiscard]] Size SizeInBytes() const
		{
			return sizeof(Index) * m_size;
		}

		[[nodiscard]] Size size() const
		{
			return m_size;
		}

	private:
		Size m_size;
	};
}
