#include "pch.hpp"
#include <DeviceContext.h>

#include <Graphics/GraphicsEngine/include/RenderDeviceBase.hpp>

#include "Graphics/GraphicsEngineD3D11/interface/EngineFactoryD3D11.h"
#include "Graphics/GraphicsEngineD3D12/interface/EngineFactoryD3D12.h"
#include "Graphics/GraphicsEngineOpenGL/interface/EngineFactoryOpenGL.h"
#include "Graphics/GraphicsEngineVulkan/interface/EngineFactoryVk.h"
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

static const char* VSSource = R"(
struct PSInput 
{ 
    float4 Pos   : SV_POSITION; 
    float3 Color : COLOR; 
};
void main(in  uint    VertId : SV_VertexID,
          out PSInput PSIn) 
{
    float4 Pos[3];
    Pos[0] = float4(-0.5, -0.5, 0.0, 1.0);
    Pos[1] = float4( 0.0, +0.5, 0.0, 1.0);
    Pos[2] = float4(+0.5, -0.5, 0.0, 1.0);
    float3 Col[3];
    Col[0] = float3(1.0, 0.0, 0.0); // red
    Col[1] = float3(0.0, 1.0, 0.0); // green
    Col[2] = float3(0.0, 0.0, 1.0); // blue
    PSIn.Pos   = Pos[VertId];
    PSIn.Color = Col[VertId];
}
)";

static const char* PSSource = R"(
struct PSInput 
{ 
    float4 Pos   : SV_POSITION; 
    float3 Color : COLOR; 
};
struct PSOutput
{ 
    float4 Color : SV_TARGET; 
};
void main(in  PSInput  PSIn,
          out PSOutput PSOut)
{
    PSOut.Color = float4(PSIn.Color.rgb, 1.0);
}
)";

void __XXECS::Renderer::LoadShader(const char* filename)
{
	
}

void __XXECS::Renderer::Exit()
{
	m_renderThread.detach();
}

void __XXECS::Renderer::Bind(const RenderArguments renderArgs)
{
	m_renderArgs = renderArgs;
	m_renderThread = std::thread([this] { RunThread(&m_renderArgs); });
}

int32_t __XXECS::Renderer::RunThread(const RenderArguments* userData)
{
	ThreadInit(userData);

	while (Application::Get().IsRunning())
		ThreadUpdate();

	ThreadExit();
	return 0;
}


void __XXECS::Renderer::ThreadInit(const RenderArguments* args)
{
    Diligent::SwapChainDesc SCDesc;
    HWND hWnd = glfwGetWin32Window(Application::Get().GetWindow().GetNativeWindow());

    switch (m_DeviceType)
    {
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
        Diligent::Win32NativeWindow Window{ hWnd };
        pFactoryD3D11->CreateSwapChainD3D11(m_pDevice, m_pImmediateContext, SCDesc, Diligent::FullScreenModeDesc{}, Window, &m_pSwapChain);

        m_NumImmediateContexts = EngineCI.NumImmediateContexts;
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
        Diligent::Win32NativeWindow Window{ hWnd };
        pFactoryD3D12->CreateSwapChainD3D12(m_pDevice, m_pImmediateContext, SCDesc, Diligent::FullScreenModeDesc{}, Window, &m_pSwapChain);

        m_NumImmediateContexts = EngineCI.NumImmediateContexts;
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

        pFactoryOpenGL->CreateDeviceAndSwapChainGL(EngineCI, &m_pDevice, &m_pImmediateContext, SCDesc, &m_pSwapChain);

        m_NumImmediateContexts = EngineCI.NumImmediateContexts;
    }
    break;
#endif


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
	        Diligent::Win32NativeWindow Window{ hWnd };
            pFactoryVk->CreateSwapChainVk(m_pDevice, m_pImmediateContext, SCDesc, Window, &m_pSwapChain);
        }

        m_NumImmediateContexts = EngineCI.NumImmediateContexts;
    }
    break;
#endif

    default:
        LOG_CORE_FATAL("Unknown/unsupported device type");
        __debugbreak();
    }


	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	
    m_pImgui = std::make_unique<Diligent::ImGuiDiligentRenderer>(m_pDevice, m_pSwapChain->GetDesc().ColorBufferFormat, m_pSwapChain->GetDesc().DepthBufferFormat, m_pSwapChain->GetDesc().BufferCount, m_pSwapChain->GetDesc().BufferCount);
    m_pImgui->CreateFontsTexture();
	ImGui_ImplGlfw_InitForOther(Application::Get().GetWindow().GetNativeWindow(), true);

	Application::Get().Init();

    // Pipeline state object encompasses configuration of all GPU stages

    Diligent::GraphicsPipelineStateCreateInfo PSOCreateInfo;

    // Pipeline state name is used by the engine to report issues.
    // It is always a good idea to give objects descriptive names.
    PSOCreateInfo.PSODesc.Name = "Simple triangle PSO";

    // This is a graphics pipeline
    PSOCreateInfo.PSODesc.PipelineType = Diligent::PIPELINE_TYPE_GRAPHICS;

    // clang-format off
    // This tutorial will render to a single render target
    PSOCreateInfo.GraphicsPipeline.NumRenderTargets = 1;
    // Set render target format which is the format of the swap chain's color buffer
    PSOCreateInfo.GraphicsPipeline.RTVFormats[0] = m_pSwapChain->GetDesc().ColorBufferFormat;
    // Use the depth buffer format from the swap chain
    PSOCreateInfo.GraphicsPipeline.DSVFormat = m_pSwapChain->GetDesc().DepthBufferFormat;
    // Primitive topology defines what kind of primitives will be rendered by this pipeline state
    PSOCreateInfo.GraphicsPipeline.PrimitiveTopology = Diligent::PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    // No back face culling for this tutorial
    PSOCreateInfo.GraphicsPipeline.RasterizerDesc.CullMode = Diligent::CULL_MODE_NONE;
    // Disable depth testing
    PSOCreateInfo.GraphicsPipeline.DepthStencilDesc.DepthEnable = false;
    // clang-format on

    LOG_CORE_TRACE("Create Shaders");
    Diligent::ShaderCreateInfo ShaderCI;
    // Tell the system that the shader source code is in HLSL.
    // For OpenGL, the engine will convert this into GLSL under the hood
    ShaderCI.SourceLanguage = Diligent::SHADER_SOURCE_LANGUAGE_HLSL;
    // OpenGL backend requires emulated combined HLSL texture samplers (g_Texture + g_Texture_sampler combination)
    ShaderCI.UseCombinedTextureSamplers = true;
    // Create a vertex shader
    Diligent::RefCntAutoPtr<Diligent::IShader> pVS;
    {
        ShaderCI.Desc.ShaderType = Diligent::SHADER_TYPE_VERTEX;
        ShaderCI.EntryPoint = "main";
        ShaderCI.Desc.Name = "Triangle vertex shader";
        ShaderCI.Source = VSSource;
        m_pDevice->CreateShader(ShaderCI, &pVS);
    }

    // Create a pixel shader
    Diligent::RefCntAutoPtr<Diligent::IShader> pPS;
    {
        ShaderCI.Desc.ShaderType = Diligent::SHADER_TYPE_PIXEL;
        ShaderCI.EntryPoint = "main";
        ShaderCI.Desc.Name = "Triangle pixel shader";
        ShaderCI.Source = PSSource;
        m_pDevice->CreateShader(ShaderCI, &pPS);
    }

    // Finally, create the pipeline state
    PSOCreateInfo.pVS = pVS;
    PSOCreateInfo.pPS = pPS;
    m_pDevice->CreateGraphicsPipelineState(PSOCreateInfo, &m_pPSO);
}

void __XXECS::Renderer::ThreadUpdate()
{
	// Handle events from the main thread.
	while (const auto ev = static_cast<EventType*>(Application::Get().GetEventManager().Pop()))
	{
		if (*ev == EventType::Resize)
		{
			const auto resizeEvent = reinterpret_cast<ResizeEvent*>(ev);

            if (m_pSwapChain)
                m_pSwapChain->Resize(resizeEvent->width, resizeEvent->height);

		}
		else if (*ev == EventType::Exit)
			Application::Get().Close();

		Application::Get().Event(ev);

		delete ev;
	}

    const auto& SCDesc = m_pSwapChain->GetDesc();
    m_pImgui->NewFrame(SCDesc.Width, SCDesc.Height, SCDesc.PreTransform);
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	Application::Get().UpdateImGui();

	Application::Get().Update();

    // Set render targets before issuing any draw command.
        // Note that Present() unbinds the back buffer if it is set as render target.
    auto* pRTV = m_pSwapChain->GetCurrentBackBufferRTV();
    auto* pDSV = m_pSwapChain->GetDepthBufferDSV();
    m_pImmediateContext->SetRenderTargets(1, &pRTV, pDSV, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

    // Clear the back buffer
    const float ClearColor[] = { 0.350f, 0.350f, 0.350f, 1.0f };
    // Let the engine perform required state transitions
    m_pImmediateContext->ClearRenderTarget(pRTV, ClearColor, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
    m_pImmediateContext->ClearDepthStencil(pDSV, Diligent::CLEAR_DEPTH_FLAG, 1.f, 0, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

    // Set the pipeline state in the immediate context
    m_pImmediateContext->SetPipelineState(m_pPSO);

    // Typically we should now call CommitShaderResources(), however shaders in this example don't
    // use any resources.

	Diligent::DrawAttribs drawAttrs;
    drawAttrs.NumVertices = 3; // Render 3 vertices
    m_pImmediateContext->Draw(drawAttrs);

    ImGui::Render();
    m_pImgui->RenderDrawData(m_pImmediateContext, ImGui::GetDrawData());

    m_pSwapChain->Present();
	
}

void __XXECS::Renderer::ThreadExit()
{
	Application::Get().Shutdown();

	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

    m_pImmediateContext->Flush();
    m_pSwapChain.Release();
	m_pDevice.Release();
}
