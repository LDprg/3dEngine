#pragma once

#include <ImGuiDiligentRenderer.hpp>
#include <TextureLoader/interface/Image.h>

namespace __XXECS
{
    struct RenderArguments
    {
        uint32_t width;
        uint32_t height;
    };

    class Renderer final
    {
    public:
        Renderer() = default;

        ~Renderer() = default;

        auto Exit() -> void;

        auto Bind(RenderArguments renderArgs) -> void;

        auto GetPipelineState() -> Diligent::RefCntAutoPtr<Diligent::IPipelineState>&
        {
            return m_pPso;
        }

        auto GetShaderResourceBinding() -> Diligent::RefCntAutoPtr<Diligent::IShaderResourceBinding>&
        {
            return m_pSrb;
        }

    private:
        auto ThreadInit() -> void;
        auto ThreadUpdate() -> void;
        static auto ThreadExit() -> void;
        auto RunThread() -> int32_t;

        std::thread m_renderThread;
        RenderArguments m_renderArgs;

        Diligent::RefCntAutoPtr<Diligent::IPipelineState> m_pPso;
        Diligent::RefCntAutoPtr<Diligent::IShaderResourceBinding> m_pSrb;
        Diligent::RefCntAutoPtr<Diligent::IBuffer> m_vsConstants;
        Diligent::RENDER_DEVICE_TYPE m_deviceType = Diligent::RENDER_DEVICE_TYPE_D3D12;
    };
}
