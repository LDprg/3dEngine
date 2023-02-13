#include "Renderable.hpp"

#include <Graphics/GraphicsTools/interface/MapHelper.hpp>

auto __XXECS::Renderable::Create(Renderable& target) -> void
{
	Diligent::BufferDesc VertBuffDesc;
	VertBuffDesc.Name           = "Vertex buffer";
	VertBuffDesc.Usage          = Diligent::USAGE_DYNAMIC;
	VertBuffDesc.CPUAccessFlags = Diligent::CPU_ACCESS_WRITE;
	VertBuffDesc.BindFlags      = Diligent::BIND_VERTEX_BUFFER;
	VertBuffDesc.Size           = target.Vertices.SizeInBytes();
	Application::Get()->GetDevice().GetNative()->CreateBuffer(VertBuffDesc, nullptr, &target.VertexBuffer);

	Diligent::BufferDesc IndBuffDesc;
	IndBuffDesc.Name      = "Index buffer";
	IndBuffDesc.Usage     = Diligent::USAGE_IMMUTABLE;
	IndBuffDesc.BindFlags = Diligent::BIND_INDEX_BUFFER;
	IndBuffDesc.Size      = target.Indices.SizeInBytes();
	Diligent::BufferData IBData;
	IBData.pData    = target.Indices;
	IBData.DataSize = target.Indices.SizeInBytes();
	Application::Get()->GetDevice().GetNative()->CreateBuffer(IndBuffDesc, &IBData, &target.IndexBuffer);
}

auto __XXECS::Renderable::Draw(Renderable& target) -> void
{
	Diligent::MapHelper<Vertex> verts(Application::Get()->GetImmediateContext().GetNative(), target.VertexBuffer,
	                                  Diligent::MAP_WRITE, Diligent::MAP_FLAG_DISCARD);
	for (Diligent::Uint32 v = 0; v < target.Vertices.size(); ++v)
		verts[v]            = target.Vertices[v];

	constexpr Diligent::Uint64 offset   = 0;
	Diligent::IBuffer*         pBuffs[] = {target.VertexBuffer};
	Application::Get()->GetImmediateContext().GetNative()->SetVertexBuffers(0, 1, pBuffs, &offset,
	                                                                        Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION,
	                                                                        Diligent::SET_VERTEX_BUFFERS_FLAG_RESET);
	Application::Get()->GetImmediateContext().GetNative()->SetIndexBuffer(target.IndexBuffer, 0,
	                                                                      Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

	Diligent::DrawIndexedAttribs drawAttrs;
	drawAttrs.IndexType  = Diligent::VT_UINT32;
	drawAttrs.NumIndices = target.Indices.size();
	drawAttrs.Flags      = Diligent::DRAW_FLAG_VERIFY_ALL;
	Application::Get()->GetImmediateContext().GetNative()->DrawIndexed(drawAttrs);
}
