/*****************************************************************/ /**
 * \file   Device.cpp
 * \brief  Device source
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#include "Engine/Renderer/Device.hpp"
#include "Engine/Core/Application.hpp"

#ifdef ENGINE_SUPPORT_D3D11
#include <Graphics/GraphicsEngineD3D11/interface/EngineFactoryD3D11.h>
#endif

#ifdef ENGINE_SUPPORT_D3D12
#include <Graphics/GraphicsEngineD3D12/interface/EngineFactoryD3D12.h>
#endif

#ifdef ENGINE_SUPPORT_OPENGL
#include <Graphics/GraphicsEngineOpenGL/interface/EngineFactoryOpenGL.h>
#endif

#ifdef ENGINE_SUPPORT_VULKAN
#include <Graphics/GraphicsEngineVulkan/interface/EngineFactoryVk.h>
#endif

auto XXECS::Device::CreateDevice(Diligent::RENDER_DEVICE_TYPE &deviceType) -> void
{
    Diligent::SwapChainDesc scDesc;

#ifdef ENGINE_PLATFORM_WINDOWS
    HWND hWnd = glfwGetWin32Window(Application::Get()->GetWindow().GetNative());
#endif

    Diligent::RefCntAutoPtr<Diligent::IRenderDevice> &pDevice = Application::Get()->GetDevice().GetNative();
    Diligent::RefCntAutoPtr<Diligent::ISwapChain> &pSwapChain = Application::Get()->GetSwapChain().GetNative();
    Diligent::RefCntAutoPtr<Diligent::IDeviceContext> &pImmediateContext = Application::Get()->GetImmediateContext().
        GetNative();

    switch (deviceType)
    {
#ifdef ENGINE_SUPPORT_VULKAN
    case Diligent::RENDER_DEVICE_TYPE_VULKAN:
    {
#    if EXPLICITLY_LOAD_ENGINE_VK_DLL
        // Load the dll and import GetEngineFactoryVk() function
        auto *getEngineFactoryVk = Diligent::LoadGraphicsEngineVk();
        auto *pFactoryVk = getEngineFactoryVk();
#else
        auto *pFactoryVk = Diligent::GetEngineFactoryVk();
#    endif
        Diligent::EngineVkCreateInfo engineCi;

        pFactoryVk->CreateDeviceAndContextsVk(engineCi, &pDevice, &pImmediateContext);

#ifdef ENGINE_PLATFORM_WINDOWS
        if (!pSwapChain && hWnd != nullptr)
        {
            Diligent::Win32NativeWindow window{hWnd};
            pFactoryVk->CreateSwapChainVk(pDevice, pImmediateContext, scDesc, window, &pSwapChain);
        }
#endif

#ifdef ENGINE_PLATFORM_LINUX

        Diligent::LinuxNativeWindow window{static_cast<Diligent::Uint32>(glfwGetX11Window(Application::Get()->GetWindow().GetNative())), glfwGetX11Display(), nullptr};

        pFactoryVk->CreateSwapChainVk(pDevice, pImmediateContext, scDesc, window, &pSwapChain);
#endif

    }
    break;
#endif

#ifdef ENGINE_SUPPORT_D3D12
    case Diligent::RENDER_DEVICE_TYPE_D3D12:
    {
#    if ENGINE_DLL
        // Load the dll and import GetEngineFactoryD3D12() function
        auto *getEngineFactoryD3D12 = Diligent::LoadGraphicsEngineD3D12();
#    endif
        Diligent::EngineD3D12CreateInfo engineCi;

        auto *pFactoryD3D12 = getEngineFactoryD3D12();
        pFactoryD3D12->CreateDeviceAndContextsD3D12(engineCi, &pDevice, &pImmediateContext);
        Diligent::Win32NativeWindow window{hWnd};
        pFactoryD3D12->CreateSwapChainD3D12(pDevice, pImmediateContext, scDesc, Diligent::FullScreenModeDesc{}, window,
                                            &pSwapChain);
    }
    break;
#endif

#ifdef ENGINE_SUPPORT_D3D11
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
#endif

#ifdef ENGINE_SUPPORT_OPENGL
    case Diligent::RENDER_DEVICE_TYPE_GLES:
    case Diligent::RENDER_DEVICE_TYPE_GL:
    {
#if EXPLICITLY_LOAD_ENGINE_GL_DLL
        // Load the dll and import GetEngineFactoryOpenGL() function
        auto *getEngineFactoryOpenGl = Diligent::LoadGraphicsEngineOpenGL();
        auto *pFactoryOpenGl = getEngineFactoryOpenGl();
#else
        auto *pFactoryOpenGl = Diligent::GetEngineFactoryOpenGL();
#endif

        Diligent::EngineGLCreateInfo engineCi;

#ifdef ENGINE_PLATFORM_WINDOWS
        engineCi.Window.hWnd = hWnd;
#endif

#ifdef ENGINE_PLATFORM_LINUX
        engineCi.Window.WindowId = glfwGetX11Window(Application::Get()->GetWindow().GetNative());
        engineCi.Window.pDisplay = glfwGetX11Display();

        glfwMakeContextCurrent(Application::Get()->GetWindow().GetNative());
#endif

        pFactoryOpenGl->CreateDeviceAndSwapChainGL(engineCi, &pDevice, &pImmediateContext, scDesc, &pSwapChain);
    }
    break;
#endif

    default: Log::CoreFatal("Unknown/unsupported device type");
    }
}
