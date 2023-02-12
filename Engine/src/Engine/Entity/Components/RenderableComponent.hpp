#pragma once
#include "Engine/Math/Vertex.hpp"

namespace __XXECS
{
	struct Renderable
	{
		Vertices Vertices;
		Indices Indices;

		Diligent::RefCntAutoPtr<Diligent::IBuffer> VertexBuffer;
		Diligent::RefCntAutoPtr<Diligent::IBuffer> IndexBuffer;
	};
}
