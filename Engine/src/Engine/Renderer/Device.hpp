/*****************************************************************/ /**
 * \file   Device.hpp
 * \brief  Rendering device management
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
// ReSharper disable CppUnusedIncludeDirective
#pragma once

#ifdef ENGINE_SUPPORT_D3D11
#include <EngineFactoryD3D11.h>
#endif

#ifdef ENGINE_SUPPORT_D3D12
#include <EngineFactoryD3D12.h>
#endif

#ifdef ENGINE_SUPPORT_OPENGL
#include <EngineFactoryOpenGL.h>
#endif

#ifdef ENGINE_SUPPORT_VULKAN
#include <EngineFactoryVk.h>
#endif

#include <RenderDevice.h>

class Diligent::RefCntAutoPtr;

namespace __XXECS
{
    class Device
    {
    public:
        Device() = default;
        virtual ~Device() = default;

        static auto CreateDevice(Diligent::RENDER_DEVICE_TYPE &deviceType) -> void;

        auto GetNative() -> Diligent::RefCntAutoPtr<Diligent::IRenderDevice>&
        {
            return m_pDevice;
        }

    private:
        Diligent::RefCntAutoPtr<Diligent::IRenderDevice> m_pDevice;
    };
}
