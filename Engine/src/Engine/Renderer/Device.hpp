#pragma once

// clang off
#include <EngineFactoryD3D11.h>
#include <EngineFactoryD3D12.h>
#include <EngineFactoryOpenGL.h>
#include <EngineFactoryVk.h>
// clang on

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


		static auto createDevice(Diligent::RENDER_DEVICE_TYPE& m_DeviceType) -> void;

		auto GetNative() -> Diligent::RefCntAutoPtr<Diligent::IRenderDevice>&
		{
			return m_pDevice;
		}

	private:
		Diligent::RefCntAutoPtr<Diligent::IRenderDevice> m_pDevice;
	};
}
