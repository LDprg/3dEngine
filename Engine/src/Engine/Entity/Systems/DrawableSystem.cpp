/*****************************************************************/ /**
 * \file   DrawableSystem.cpp
 * \brief  DrawableSystem Source
 * 
 * \author LD
 * \date   March 2023
 *********************************************************************/
#include "DrawableSystem.hpp"

#include <Engine/Core/Application.hpp>

using namespace XXECS::Entity;

auto DrawableSystem::Create(const entt::entity &entity) -> void
{
    auto &target = GetEntityManager().get<Drawable>(entity);

    Diligent::BufferDesc vertexBuffDesc;
    vertexBuffDesc.Name = "Vertex buffer";
    vertexBuffDesc.Usage = Diligent::USAGE_DEFAULT;
    vertexBuffDesc.BindFlags = Diligent::BIND_VERTEX_BUFFER;
    vertexBuffDesc.Size = target.vertices.SizeInBytes();
    Application::Get()->GetDevice().GetNative()->CreateBuffer(vertexBuffDesc, nullptr, &target.vertexBuffer);

    Diligent::BufferDesc indexBuffDesc;
    indexBuffDesc.Name = "Index buffer";
    indexBuffDesc.Usage = Diligent::USAGE_IMMUTABLE;
    indexBuffDesc.BindFlags = Diligent::BIND_INDEX_BUFFER;
    indexBuffDesc.Size = target.indices.SizeInBytes();
    Diligent::BufferData ibData;
    ibData.pData = target.indices;
    ibData.DataSize = target.indices.SizeInBytes();
    Application::Get()->GetDevice().GetNative()->CreateBuffer(indexBuffDesc, &ibData, &target.indexBuffer);
}

auto DrawableSystem::Run(const entt::entity &entity) -> void
{
    auto &target = GetEntityManager().get<Drawable>(entity);

    constexpr Diligent::Uint64 offset = 0;
    Diligent::IBuffer *pBuffs[] = {target.vertexBuffer};
    Application::Get()->GetImmediateContext().GetNative()->SetVertexBuffers(
        0, 1, pBuffs, &offset, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION,
        Diligent::SET_VERTEX_BUFFERS_FLAG_RESET);
    Application::Get()->GetImmediateContext().GetNative()->SetIndexBuffer(
        target.indexBuffer, 0, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

    Diligent::DrawIndexedAttribs drawAttrs;
    drawAttrs.IndexType = Diligent::VT_UINT32;
    drawAttrs.NumIndices = target.indices.size();
    drawAttrs.Flags = Diligent::DRAW_FLAG_VERIFY_ALL;
    Application::Get()->GetImmediateContext().GetNative()->DrawIndexed(drawAttrs);
}
