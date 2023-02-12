#pragma once
#include <Buffer.h>
#include <Common/interface/RefCntAutoPtr.hpp>
#include <Graphics/GraphicsTools/interface/MapHelper.hpp>

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

		void Create()
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
			Diligent::MapHelper<Vertex> verts(Application::Get().GetImmediateContext().GetNative(), VertexBuffer,
				Diligent::MAP_WRITE, Diligent::MAP_FLAG_DISCARD);
			for (Diligent::Uint32 v = 0; v < Vertices.size(); ++v)
				verts[v] = Vertices[v];

			const Diligent::Uint64 offset = 0;
			Diligent::IBuffer* pBuffs[] = {
				VertexBuffer
			};
			Application::Get().GetImmediateContext().GetNative()->SetVertexBuffers(0, 1, pBuffs, &offset,
				Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION,
				Diligent::SET_VERTEX_BUFFERS_FLAG_RESET);
			Application::Get().GetImmediateContext().GetNative()->SetIndexBuffer(IndexBuffer, 0,
				Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

			Diligent::DrawIndexedAttribs drawAttrs;
			drawAttrs.IndexType = Diligent::VT_UINT32;
			drawAttrs.NumIndices = Indices.size();
			drawAttrs.Flags = Diligent::DRAW_FLAG_VERIFY_ALL;
			Application::Get().GetImmediateContext().GetNative()->DrawIndexed(drawAttrs);
		}
	};
}
