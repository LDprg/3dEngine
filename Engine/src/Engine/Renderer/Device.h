#pragma once

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <EngineFactory.h>
#include <EngineFactoryD3D11.h>
#include <EngineFactoryD3D12.h>
#include <EngineFactoryOpenGL.h>
#include <EngineFactoryVk.h>

#include "Engine/Core/Application.h"

namespace __XXECS
{
	class Device
	{
	public:
		static void createDevice(Diligent::RENDER_DEVICE_TYPE& m_DeviceType);

		Diligent::RefCntAutoPtr<Diligent::IRenderDevice>& GetNative()
		{
			return m_pDevice;
		}

	private:
		Diligent::RefCntAutoPtr<Diligent::IRenderDevice> m_pDevice;
	};
}
