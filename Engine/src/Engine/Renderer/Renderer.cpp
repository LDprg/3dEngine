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
    Device::createDevice(m_DeviceType);

    Application::Get().GetImguiManager().Init();

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
    PSOCreateInfo.GraphicsPipeline.RTVFormats[0] = Application::Get().GetSwapChain().GetDesc().ColorBufferFormat;
    // Use the depth buffer format from the swap chain
    PSOCreateInfo.GraphicsPipeline.DSVFormat = Application::Get().GetSwapChain().GetDesc().DepthBufferFormat;
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
        Application::Get().GetDevice().GetNative()->CreateShader(ShaderCI, &pVS);
    }

    // Create a pixel shader
    Diligent::RefCntAutoPtr<Diligent::IShader> pPS;
    {
        ShaderCI.Desc.ShaderType = Diligent::SHADER_TYPE_PIXEL;
        ShaderCI.EntryPoint = "main";
        ShaderCI.Desc.Name = "Triangle pixel shader";
        ShaderCI.Source = PSSource;
        Application::Get().GetDevice().GetNative()->CreateShader(ShaderCI, &pPS);
    }

    // Finally, create the pipeline state
    PSOCreateInfo.pVS = pVS;
    PSOCreateInfo.pPS = pPS;
    Application::Get().GetDevice().GetNative()->CreateGraphicsPipelineState(PSOCreateInfo, &m_pPSO);
}

void __XXECS::Renderer::ThreadUpdate()
{
    static int oldWidth;
    static int oldHeight;
    int m_width;
    int m_height;
    glfwGetWindowSize(Application::Get().GetWindow().GetNative(), &m_width, &m_height);
    if (m_width != oldWidth || m_height != oldHeight)
    {
        const auto resize = new ResizeEvent;
        resize->width = m_width;
        resize->height = m_height;
        Application::Get().GetEventManager().Push(resize);
    }
    oldWidth = m_width;
    oldHeight = m_height;

	// Handle events from the main thread.
	while (const auto ev = static_cast<EventType*>(Application::Get().GetEventManager().Pop()))
	{
		if (*ev == EventType::Resize)
		{
			const auto resizeEvent = reinterpret_cast<ResizeEvent*>(ev);

            Application::Get().GetSwapChain().GetNative()->Resize(resizeEvent->width, resizeEvent->height);
		}
		else if (*ev == EventType::Exit)
			Application::Get().Close();

        Application::Get().GetImguiManager().Event(ev);
		Application::Get().Event(ev);

		delete ev;
	}

    Application::Get().GetImguiManager().NewFrame();

	Application::Get().UpdateImGui();

	Application::Get().Update();

    auto& m_pImmediateContext = Application::Get().GetImmediateContext().GetNative();

    // Set render targets before issuing any draw command.
        // Note that Present() unbinds the back buffer if it is set as render target.
    auto* pRTV = Application::Get().GetSwapChain().GetNative()->GetCurrentBackBufferRTV();
    auto* pDSV = Application::Get().GetSwapChain().GetNative()->GetDepthBufferDSV();
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

    Application::Get().GetImguiManager().Render();

    Application::Get().GetSwapChain().Present();
	
}

void __XXECS::Renderer::ThreadExit()
{
	Application::Get().Shutdown();

    Application::Get().GetImguiManager().Destory();

    Application::Get().GetImmediateContext().GetNative()->Flush();
    Application::Get().GetSwapChain().GetNative().Release();
    Application::Get().GetDevice().GetNative().Release();
}
