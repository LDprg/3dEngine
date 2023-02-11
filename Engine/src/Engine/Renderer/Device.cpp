#include <Engine/Renderer/Device.h>

void __XXECS::Device::createDevice(Diligent::RENDER_DEVICE_TYPE& m_DeviceType)
{
	Diligent::SwapChainDesc SCDesc;
	HWND hWnd = glfwGetWin32Window(Application::Get().GetWindow().GetNative());

	Diligent::RefCntAutoPtr<Diligent::IRenderDevice>& m_pDevice = Application::Get().GetDevice().GetNative();
	Diligent::RefCntAutoPtr<Diligent::ISwapChain>& m_pSwapChain = Application::Get().GetSwapChain().GetNative();
	Diligent::RefCntAutoPtr<Diligent::IDeviceContext>& m_pImmediateContext = Application::Get().GetImmediateContext().
		GetNative();

	switch (m_DeviceType)
	{
#if VULKAN_SUPPORTED
	case Diligent::RENDER_DEVICE_TYPE_VULKAN:
		{
#    if EXPLICITLY_LOAD_ENGINE_VK_DLL
			// Load the dll and import GetEngineFactoryVk() function
			auto GetEngineFactoryVk = Diligent::LoadGraphicsEngineVk();
#    endif
			Diligent::EngineVkCreateInfo EngineCI;

			auto* pFactoryVk = GetEngineFactoryVk();
			pFactoryVk->CreateDeviceAndContextsVk(EngineCI, &m_pDevice, &m_pImmediateContext);

			if (!m_pSwapChain && hWnd != nullptr)
			{
				Diligent::Win32NativeWindow Window{hWnd};
				pFactoryVk->CreateSwapChainVk(m_pDevice, m_pImmediateContext, SCDesc, Window, &m_pSwapChain);
			}
		}
		break;
#endif

#if D3D12_SUPPORTED
	case Diligent::RENDER_DEVICE_TYPE_D3D12:
		{
#    if ENGINE_DLL
			// Load the dll and import GetEngineFactoryD3D12() function
			auto GetEngineFactoryD3D12 = Diligent::LoadGraphicsEngineD3D12();
#    endif
			Diligent::EngineD3D12CreateInfo EngineCI;

			auto* pFactoryD3D12 = GetEngineFactoryD3D12();
			pFactoryD3D12->CreateDeviceAndContextsD3D12(EngineCI, &m_pDevice, &m_pImmediateContext);
			Diligent::Win32NativeWindow Window{hWnd};
			pFactoryD3D12->CreateSwapChainD3D12(m_pDevice, m_pImmediateContext, SCDesc, Diligent::FullScreenModeDesc{},
			                                    Window, &m_pSwapChain);
		}
		break;
#endif

#if D3D11_SUPPORTED
	case Diligent::RENDER_DEVICE_TYPE_D3D11:
		{
			Diligent::EngineD3D11CreateInfo EngineCI;
#    if ENGINE_DLL
			// Load the dll and import GetEngineFactoryD3D11() function
			auto* GetEngineFactoryD3D11 = Diligent::LoadGraphicsEngineD3D11();
#    endif
			auto* pFactoryD3D11 = GetEngineFactoryD3D11();
			pFactoryD3D11->CreateDeviceAndContextsD3D11(EngineCI, &m_pDevice, &m_pImmediateContext);
			Diligent::Win32NativeWindow Window{hWnd};
			pFactoryD3D11->CreateSwapChainD3D11(m_pDevice, m_pImmediateContext, SCDesc, Diligent::FullScreenModeDesc{},
			                                    Window, &m_pSwapChain);
		}
		break;
#endif

#if GL_SUPPORTED
	case Diligent::RENDER_DEVICE_TYPE_GL:
		{
#    if EXPLICITLY_LOAD_ENGINE_GL_DLL
			// Load the dll and import GetEngineFactoryOpenGL() function
			auto GetEngineFactoryOpenGL = Diligent::LoadGraphicsEngineOpenGL();
#    endif
			auto* pFactoryOpenGL = GetEngineFactoryOpenGL();

			Diligent::EngineGLCreateInfo EngineCI;
			EngineCI.Window.hWnd = hWnd;

			pFactoryOpenGL->CreateDeviceAndSwapChainGL(EngineCI, &m_pDevice, &m_pImmediateContext, SCDesc,
			                                           &m_pSwapChain);
		}
		break;
#endif

	default:
		LOG_CORE_FATAL("Unknown/unsupported device type");
		__debugbreak();
	}
}
