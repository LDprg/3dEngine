/*****************************************************************/ /**
 * \file   Device.hpp
 * \brief  Rendering device management
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

#include <Common/interface/RefCntAutoPtr.hpp>
#include <Graphics/GraphicsEngine/interface/RenderDevice.h>

namespace XXECS
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
