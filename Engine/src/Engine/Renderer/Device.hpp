/*****************************************************************/ /**
 * \file   Device.hpp
 * \brief  Rendering device management
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
// ReSharper disable CppUnusedIncludeDirective
#pragma once

#include <EngineFactoryD3D11.h>
#include <EngineFactoryD3D12.h>
#include <EngineFactoryOpenGL.h>
#include <EngineFactoryVk.h>

#include <Common/interface/RefCntAutoPtr.hpp>

namespace __XXECS
{
    class Device
    {
    public:
        Device() = default;

        ~Device()
        {
            m_pDevice.Release();
        }


        static auto CreateDevice(Diligent::RENDER_DEVICE_TYPE &deviceType) -> void;

        auto GetNative() -> Diligent::RefCntAutoPtr<Diligent::IRenderDevice>&
        {
            return m_pDevice;
        }

    private:
        Diligent::RefCntAutoPtr<Diligent::IRenderDevice> m_pDevice;
    };
}
