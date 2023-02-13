#pragma once
#include <Buffer.h>
#include <Common/interface/RefCntAutoPtr.hpp>

#include "Engine/Math/Vertex.hpp"

namespace __XXECS
{
	struct Renderable
	{
		Vertices Vertices;
		Indices  Indices;

		Diligent::RefCntAutoPtr<Diligent::IBuffer> VertexBuffer;
		Diligent::RefCntAutoPtr<Diligent::IBuffer> IndexBuffer;

		static auto Create(Renderable& target) -> void;
		static auto Draw(Renderable& target) -> void;
	};
}
