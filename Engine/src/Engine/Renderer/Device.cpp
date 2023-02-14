/*****************************************************************/ /**
 * \file   Device.cpp
 * \brief  Device source
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#include "Engine/Renderer/Device.hpp"

auto __XXECS::Device::CreateDevice(Diligent::RENDER_DEVICE_TYPE &deviceType) -> void
{
    Diligent::SwapChainDesc scDesc;
    HWND hWnd = glfwGetWin32Window(Application::Get()->GetWindow().GetNative());

    Diligent::RefCntAutoPtr<Diligent::IRenderDevice> &pDevice = Application::Get()->GetDevice().GetNative();
    Diligent::RefCntAutoPtr<Diligent::ISwapChain> &pSwapChain = Application::Get()->GetSwapChain().GetNative();
    Diligent::RefCntAutoPtr<Diligent::IDeviceContext> &pImmediateContext = Application::Get()->GetImmediateContext().
        GetNative();

    switch (deviceType)
    {
    case Diligent::RENDER_DEVICE_TYPE_VULKAN:
    {
#    if EXPLICITLY_LOAD_ENGINE_VK_DLL
        // Load the dll and import GetEngineFactoryVk() function
        auto getEngineFactoryVk = Diligent::LoadGraphicsEngineVk();
#    endif
        Diligent::EngineVkCreateInfo engineCi;

        auto *pFactoryVk = getEngineFactoryVk();
        pFactoryVk->CreateDeviceAndContextsVk(engineCi, &pDevice, &pImmediateContext);

        if (!pSwapChain && hWnd != nullptr)
        {
            Diligent::Win32NativeWindow window{hWnd};
            pFactoryVk->CreateSwapChainVk(pDevice, pImmediateContext, scDesc, window, &pSwapChain);
        }
    }
    break;

    case Diligent::RENDER_DEVICE_TYPE_D3D12:
    {
#    if ENGINE_DLL
        // Load the dll and import GetEngineFactoryD3D12() function
        auto getEngineFactoryD3D12 = Diligent::LoadGraphicsEngineD3D12();
#    endif
        Diligent::EngineD3D12CreateInfo engineCi;

        auto *pFactoryD3D12 = getEngineFactoryD3D12();
        pFactoryD3D12->CreateDeviceAndContextsD3D12(engineCi, &pDevice, &pImmediateContext);
        Diligent::Win32NativeWindow window{hWnd};
        pFactoryD3D12->CreateSwapChainD3D12(pDevice, pImmediateContext, scDesc, Diligent::FullScreenModeDesc{}, window,
                                            &pSwapChain);
    }
    break;

    case Diligent::RENDER_DEVICE_TYPE_D3D11:
    {
        Diligent::EngineD3D11CreateInfo engineCi;
#    if ENGINE_DLL
        // Load the dll and import GetEngineFactoryD3D11() function
        auto *getEngineFactoryD3D11 = Diligent::LoadGraphicsEngineD3D11();
#    endif
        auto *pFactoryD3D11 = getEngineFactoryD3D11();
        pFactoryD3D11->CreateDeviceAndContextsD3D11(engineCi, &pDevice, &pImmediateContext);
        Diligent::Win32NativeWindow window{hWnd};
        pFactoryD3D11->CreateSwapChainD3D11(pDevice, pImmediateContext, scDesc, Diligent::FullScreenModeDesc{}, window,
                                            &pSwapChain);
    }
    break;

    case Diligent::RENDER_DEVICE_TYPE_GL:
    {
#    if EXPLICITLY_LOAD_ENGINE_GL_DLL
        // Load the dll and import GetEngineFactoryOpenGL() function
        auto getEngineFactoryOpenGl = Diligent::LoadGraphicsEngineOpenGL();
#    endif
        auto *pFactoryOpenGl = getEngineFactoryOpenGl();

        Diligent::EngineGLCreateInfo engineCi;
        engineCi.Window.hWnd = hWnd;

        pFactoryOpenGl->CreateDeviceAndSwapChainGL(engineCi, &pDevice, &pImmediateContext, scDesc, &pSwapChain);
    }
    break;

    case Diligent::RENDER_DEVICE_TYPE_UNDEFINED:
    case Diligent::RENDER_DEVICE_TYPE_GLES:
    case Diligent::RENDER_DEVICE_TYPE_METAL:
    case Diligent::RENDER_DEVICE_TYPE_COUNT: LOG_CORE_FATAL("Unknown/unsupported device type");
        __debugbreak();
    }
}
