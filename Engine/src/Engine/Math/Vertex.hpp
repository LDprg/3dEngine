#pragma once

#include <initializer_list>
#include <memory>

#include <BasicTypes.h>

namespace __XXECS
{
	typedef Diligent::Uint32 Index;

    template<typename T>
	struct Vertex
	{
		Position<T> pos;
		Color<T> color;
	};

	struct Vertices
	{
		std::unique_ptr<Vertex<float>[]> data;
		size_t size;

		Vertices() = default;
		Vertices(Vertex<float>* data, size_t size) : data(data), size(size) {}
		Vertices(std::initializer_list<Vertex<float>> ilist) : size(ilist.size())
		{
			data = std::make_unique<Vertex<float>[]>(size);
			std::copy(ilist.begin(), ilist.end(), data.get());
		}

		size_t getSize() const
		{
			return sizeof(*data.get()) * size;
		}

		operator Vertex<float>* () const
		{
			return data.get();
		}
	};
	
    struct Indices
    {
		std::unique_ptr<Index[]> data;
    	size_t size;

		Indices() = default;
		Indices(Index* data, size_t size) : data(data), size(size) {}
		Indices(std::initializer_list<Index> ilist) : size(ilist.size())
		{
			data = std::make_unique<Index[]>(size);
			std::copy(ilist.begin(), ilist.end(), data.get());
		}

		size_t getSize() const
		{
			return sizeof(*data.get()) * size;
		}

		operator Index* () const
		{
			return data.get();
		}
    };
}
