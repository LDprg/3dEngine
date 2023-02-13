#pragma once

#include <EngineFactoryD3D11.h>
#include <EngineFactoryD3D12.h>
#include <EngineFactoryOpenGL.h>
#include <EngineFactoryVk.h>

#include "Engine/Core/Application.hpp"

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


		static void createDevice(Diligent::RENDER_DEVICE_TYPE& m_DeviceType);

		Diligent::RefCntAutoPtr<Diligent::IRenderDevice>& GetNative()
		{
			return m_pDevice;
		}

	private:
		Diligent::RefCntAutoPtr<Diligent::IRenderDevice> m_pDevice;
	};
}
