#pragma once

#include <initializer_list>
#include <vector>

#include <BasicTypes.h>

#include "Vector.hpp"

namespace __XXECS
{
	typedef Diligent::Uint32 Index;

    template<typename T>
	struct Vertex
	{
		Position<T> pos;
		Color<T> color;
	};


	class Vertices : public std::vector<Vertex<float>>
	{
	public:
		Vertices() : std::vector<Vertex<float>>() {}
		Vertices(std::initializer_list<Vertex<float>> ilist) : std::vector<Vertex<float>>(ilist)
		{
			shrink_to_fit();
		}

		operator void* () const
		{
			return const_cast<Vertex<float>*>(data());
		}

		operator Vertex<float>* ()
		{
			return data();
		}

		size_t sizeInBytes() const
		{
			return sizeof(Vertex<float>) * size();
		}
	};

	class Indices : public std::vector<Index>
	{
	public:
		Indices() : std::vector<Index>() {}
		Indices(std::initializer_list<Index> ilist) : std::vector<Index>(ilist)
		{
			shrink_to_fit();
		}

		operator void* () const
		{
			return const_cast<Index*>(data());
		}

		operator Index* ()
		{
			return data();
		}

		size_t sizeInBytes() const
		{
			return sizeof(Index) * size();
		}
	};
}
