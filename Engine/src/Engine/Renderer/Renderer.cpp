#include <DeviceContext.h>
#include <RenderDevice.h>
#include "pch.hpp"

#include <GLFW/glfw3.h>

#include "Engine/Core/Application.hpp"

static const char* VSSource = R"(
struct VSInput
{
    float4 Pos   : ATTRIB0;
    float4 Color : ATTRIB1;
};
struct PSInput 
{ 
    float4 Pos   : SV_POSITION; 
    float4 Color : COLOR; 
};
void main(in  VSInput VSIn,
          out PSInput PSIn) 
{
	PSIn.Pos = VSIn.Pos;
	PSIn.Color = VSIn.Color;
}
)";

static const char* PSSource = R"(
struct PSInput 
{ 
    float4 Pos   : SV_POSITION; 
    float4 Color : COLOR; 
};
struct PSOutput
{ 
    float4 Color : SV_TARGET; 
};
void main(in  PSInput  PSIn,
          out PSOutput PSOut)
{
    PSOut.Color = PSIn.Color;
}
)";

void __XXECS::Renderer::Exit()
{
	m_renderThread.detach();
}

void __XXECS::Renderer::Bind(const RenderArguments renderArgs)
{
	m_renderArgs = renderArgs;
	m_renderThread = std::thread([this]
	{
		RunThread(&m_renderArgs);
	});
}

int32_t __XXECS::Renderer::RunThread(const RenderArguments* userData)
{
	ThreadInit(userData);

	while (Application::Get()->IsRunning())
		ThreadUpdate();

	ThreadExit();
	return 0;
}


void __XXECS::Renderer::ThreadInit(const RenderArguments* args)
{
	Device::createDevice(m_DeviceType);

	Application::Get()->GetImGuiManager().Init();

	Application::Get()->Init();

	Diligent::BlendStateDesc BlendState;
	BlendState.RenderTargets[0].BlendEnable = true;
	BlendState.RenderTargets[0].SrcBlend = Diligent::BLEND_FACTOR_SRC_ALPHA;
	BlendState.RenderTargets[0].DestBlend = Diligent::BLEND_FACTOR_INV_SRC_ALPHA;

	// Pipeline state object encompasses configuration of all GPU stages

	Diligent::GraphicsPipelineStateCreateInfo PSOCreateInfo;

	// Pipeline state name is used by the engine to report issues.
	// It is always a good idea to give objects descriptive names.
	PSOCreateInfo.PSODesc.Name = "Main PSO";

	// This is a graphics pipeline
	PSOCreateInfo.PSODesc.PipelineType = Diligent::PIPELINE_TYPE_GRAPHICS;

	// This tutorial will render to a single render target
	PSOCreateInfo.GraphicsPipeline.NumRenderTargets = 1;
	// Set render target format which is the format of the swap chain's color buffer
	PSOCreateInfo.GraphicsPipeline.RTVFormats[0] = Application::Get()->GetSwapChain().GetDesc().ColorBufferFormat;
	// Use the depth buffer format from the swap chain
	PSOCreateInfo.GraphicsPipeline.DSVFormat = Application::Get()->GetSwapChain().GetDesc().DepthBufferFormat;
	// Primitive topology defines what kind of primitives will be rendered by this pipeline state
	PSOCreateInfo.GraphicsPipeline.PrimitiveTopology = Diligent::PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	// No back face culling for this tutorial
	PSOCreateInfo.GraphicsPipeline.RasterizerDesc.CullMode = Diligent::CULL_MODE_BACK;
	// Disable depth testing
	PSOCreateInfo.GraphicsPipeline.DepthStencilDesc.DepthEnable = true;

	PSOCreateInfo.GraphicsPipeline.BlendDesc = BlendState;

	Diligent::LayoutElement LayoutElems[] =
	{
		// Attribute 0 - vertex position
		Diligent::LayoutElement{0, 0, 4, Diligent::VT_FLOAT32, Diligent::False},
		// Attribute 1 - vertex color
		Diligent::LayoutElement{1, 0, 4, Diligent::VT_FLOAT32, Diligent::False}
	};
	PSOCreateInfo.GraphicsPipeline.InputLayout.LayoutElements = LayoutElems;
	PSOCreateInfo.GraphicsPipeline.InputLayout.NumElements = _countof(LayoutElems);

	LOG_CORE_TRACE("Create Shaders");
	Diligent::ShaderCreateInfo ShaderCI;
	// Tell the system that the shader source code is in HLSL.
	// For OpenGL, the engine will convert this into GLSL under the hood
	ShaderCI.SourceLanguage = Diligent::SHADER_SOURCE_LANGUAGE_HLSL;

	// Create a vertex shader
	Diligent::RefCntAutoPtr<Diligent::IShader> pVS;
	{
		ShaderCI.Desc.ShaderType = Diligent::SHADER_TYPE_VERTEX;
		ShaderCI.EntryPoint = "main";
		ShaderCI.Desc.Name = "Triangle vertex shader";
		ShaderCI.Source = VSSource;
		Application::Get()->GetDevice().GetNative()->CreateShader(ShaderCI, &pVS);
	}

	// Create a pixel shader
	Diligent::RefCntAutoPtr<Diligent::IShader> pPS;
	{
		ShaderCI.Desc.ShaderType = Diligent::SHADER_TYPE_PIXEL;
		ShaderCI.EntryPoint = "main";
		ShaderCI.Desc.Name = "Triangle pixel shader";
		ShaderCI.Source = PSSource;
		Application::Get()->GetDevice().GetNative()->CreateShader(ShaderCI, &pPS);
	}

	// Finally, create the pipeline state
	PSOCreateInfo.pVS = pVS;
	PSOCreateInfo.pPS = pPS;

	// Define variable type that will be used by default
	PSOCreateInfo.PSODesc.ResourceLayout.DefaultVariableType = Diligent::SHADER_RESOURCE_VARIABLE_TYPE_STATIC;

	Application::Get()->GetDevice().GetNative()->CreateGraphicsPipelineState(PSOCreateInfo, &m_pPSO);

	// Since we did not explcitly specify the type for 'Constants' variable, default
	// type (SHADER_RESOURCE_VARIABLE_TYPE_STATIC) will be used. Static variables never
	// change and are bound directly through the pipeline state object.
	auto* temp = m_pPSO->GetStaticVariableByName(Diligent::SHADER_TYPE_VERTEX, "Constants");
	if (temp)
		temp->Set(m_VSConstants);

	// Create a shader resource binding object and bind all static resources in it
	m_pPSO->CreateShaderResourceBinding(&m_pSRB, true);
}

void __XXECS::Renderer::ThreadUpdate()
{
	static int oldWidth;
	static int oldHeight;
	int m_width;
	int m_height;
	glfwGetWindowSize(Application::Get()->GetWindow().GetNative(), &m_width, &m_height);
	if (m_width != oldWidth || m_height != oldHeight)
	{
		ResizeEvent resize = ResizeEvent();
		resize.width = m_width;
		resize.height = m_height;
		Application::Get()->GetEventManager().Push(resize);
	}
	oldWidth = m_width;
	oldHeight = m_height;

	// Handle events from the main thread.
	while (true)
	{
		const std::any ev = Application::Get()->GetEventManager().Pop();
		if (!ev.has_value())
			break;

		if (ev.type() == typeid(ResizeEvent))
		{
			const auto resizeEvent = any_cast<ResizeEvent>(ev);

			Application::Get()->GetSwapChain().GetNative()->Resize(resizeEvent.width, resizeEvent.height);
		}
		else if (ev.type() == typeid(ExitEvent))
			Application::Get()->Close();

		Application::Get()->GetImGuiManager().Event(ev);
		Application::Get()->Event(ev);
	}

	Application::Get()->GetImGuiManager().NewFrame();

	auto& m_pImmediateContext = Application::Get()->GetImmediateContext().GetNative();

	// Set render targets before issuing any draw command.
	// Note that Present() unbinds the back buffer if it is set as render target.
	auto* pRTV = Application::Get()->GetSwapChain().GetNative()->GetCurrentBackBufferRTV();
	auto* pDSV = Application::Get()->GetSwapChain().GetNative()->GetDepthBufferDSV();
	m_pImmediateContext->SetRenderTargets(1, &pRTV, pDSV, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

	// Let the engine perform required state transitions
	m_pImmediateContext->ClearRenderTarget(pRTV, Application::Get()->GetClearColor(),
	                                       Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
	m_pImmediateContext->ClearDepthStencil(pDSV, Diligent::CLEAR_DEPTH_FLAG, 1.f, 0,
	                                       Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

	Application::Get()->Update();

	Application::Get()->ImGui();

	// Set the pipeline state in the immediate context
	m_pImmediateContext->SetPipelineState(m_pPSO);
	m_pImmediateContext->CommitShaderResources(m_pSRB, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

	Application::Get()->Render();

	Application::Get()->GetImGuiManager().Render();

	Application::Get()->GetSwapChain().Present();
}

void __XXECS::Renderer::ThreadExit()
{
	Application::Get()->Shutdown();

	Application::Get()->GetImGuiManager().Destroy();

	Application::Get()->GetImmediateContext().GetNative()->Flush();
	Application::Get()->GetSwapChain().GetNative().Release();
	Application::Get()->GetDevice().GetNative().Release();
}
