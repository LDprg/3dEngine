#pragma once
#include <Buffer.h>
#include <Common/interface/RefCntAutoPtr.hpp>

#include "Engine/Core/Application.h"
#include "Engine/Math/Vertex.hpp"

namespace __XXECS
{
	struct Renderable
	{
		Vertices Vertices;
		Indices Indices;

		Diligent::RefCntAutoPtr<Diligent::IBuffer> VertexBuffer;
		Diligent::RefCntAutoPtr<Diligent::IBuffer> IndexBuffer;

		void Create(Diligent::Uint64 VertexSize, Diligent::Uint64 IndexSize)
		{
			Diligent::BufferDesc VertBuffDesc;
			VertBuffDesc.Name = "Vertex buffer";
			VertBuffDesc.Usage = Diligent::USAGE_DYNAMIC;
			VertBuffDesc.CPUAccessFlags = Diligent::CPU_ACCESS_WRITE;
			VertBuffDesc.BindFlags = Diligent::BIND_VERTEX_BUFFER;
			VertBuffDesc.Size = Vertices.sizeInBytes();
			Application::Get().GetDevice().GetNative()->CreateBuffer(VertBuffDesc, nullptr, &VertexBuffer);

			Diligent::BufferDesc IndBuffDesc;
			IndBuffDesc.Name = "Index buffer";
			IndBuffDesc.Usage = Diligent::USAGE_IMMUTABLE;
			IndBuffDesc.BindFlags = Diligent::BIND_INDEX_BUFFER;
			IndBuffDesc.Size = Indices.sizeInBytes();
			Diligent::BufferData IBData;
			IBData.pData = Indices;
			IBData.DataSize = Indices.sizeInBytes();
			Application::Get().GetDevice().GetNative()->CreateBuffer(IndBuffDesc, &IBData, &IndexBuffer);
		}

		void Draw()
		{
			Diligent::DrawIndexedAttribs drawAttrs;
			drawAttrs.IndexType = Diligent::VT_UINT32;
			drawAttrs.NumIndices = Vertices.size();
			drawAttrs.Flags = Diligent::DRAW_FLAG_VERIFY_ALL;
			Application::Get().GetImmediateContext().GetNative()->DrawIndexed(drawAttrs);
		}
	};
}
