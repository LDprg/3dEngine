/*****************************************************************/ /**
 * \file   Renderer.hpp
 * \brief  Renderer management
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

#include <Common/interface/RefCntAutoPtr.hpp>
#include <Graphics/GraphicsEngine/interface/BlendState.h>
#include <Graphics/GraphicsEngine/interface/Buffer.h>
#include <Graphics/GraphicsEngine/interface/PipelineState.h>
#include <Graphics/GraphicsEngine/interface/RenderDevice.h>
#include <Graphics/GraphicsEngine/interface/ShaderResourceBinding.h>

namespace XXECS
{
    class Renderer final
    {
    public:
        Renderer() = default;

        ~Renderer() = default;

        auto Update() -> void;

        auto Init() -> void;

        auto GetPipelineState() -> Diligent::RefCntAutoPtr<Diligent::IPipelineState>&
        {
            return m_pPso;
        }

        auto GetShaderResourceBinding() -> Diligent::RefCntAutoPtr<Diligent::IShaderResourceBinding>&
        {
            return m_pSrb;
        }

    private:
        Diligent::RefCntAutoPtr<Diligent::IPipelineState> m_pPso;
        Diligent::RefCntAutoPtr<Diligent::IShaderResourceBinding> m_pSrb;
        Diligent::RefCntAutoPtr<Diligent::IBuffer> m_vsConstants;
        Diligent::RENDER_DEVICE_TYPE m_deviceType = Diligent::RENDER_DEVICE_TYPE_D3D11;
    };
}
