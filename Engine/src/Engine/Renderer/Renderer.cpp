/*****************************************************************/ /**
 * \file   Renderer.cpp
 * \brief  Renderer source
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#include <DeviceContext.h>
#include <RenderDevice.h>

#include "Engine/Core/Application.hpp"

static const char *vsSource = R"(
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

static const char *psSource = R"(
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

auto __XXECS::Renderer::Exit() -> void
{
    m_renderThread.detach();
}

auto __XXECS::Renderer::Init() -> void
{
    m_renderThread = std::thread([this]
    {
        RunThread();
    });
}

auto __XXECS::Renderer::RunThread() -> int32_t
{
    ThreadInit();

    while (Application::Get()->IsRunning())
        ThreadUpdate();

    ThreadExit();
    return 0;
}


auto __XXECS::Renderer::ThreadInit() -> void
{
    Device::CreateDevice(m_deviceType);

    Application::Get()->GetImGuiManager().Init();

    Application::Get()->Init();

    // Pipeline state object encompasses configuration of all GPU stages

    Diligent::GraphicsPipelineStateCreateInfo psoCreateInfo;

    // Pipeline state name is used by the engine to report issues.
    // It is always a good idea to give objects descriptive names.
    psoCreateInfo.PSODesc.Name = "Main PSO";

    // This is a graphics pipeline
    psoCreateInfo.PSODesc.PipelineType = Diligent::PIPELINE_TYPE_GRAPHICS;

    // This tutorial will render to a single render target
    psoCreateInfo.GraphicsPipeline.NumRenderTargets = 1;
    // Set render target format which is the format of the swap chain's color buffer
    psoCreateInfo.GraphicsPipeline.RTVFormats[0] = Application::Get()->GetSwapChain().GetDesc().ColorBufferFormat;
    // Use the depth buffer format from the swap chain
    psoCreateInfo.GraphicsPipeline.DSVFormat = Application::Get()->GetSwapChain().GetDesc().DepthBufferFormat;
    // Primitive topology defines what kind of primitives will be rendered by this pipeline state
    psoCreateInfo.GraphicsPipeline.PrimitiveTopology = Diligent::PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    // No back face culling for this tutorial
    psoCreateInfo.GraphicsPipeline.RasterizerDesc.CullMode = Diligent::CULL_MODE_BACK;
    // Disable depth testing
    psoCreateInfo.GraphicsPipeline.DepthStencilDesc.DepthEnable = true;


    Diligent::BlendStateDesc &bsDesc = psoCreateInfo.GraphicsPipeline.BlendDesc;
    bsDesc.IndependentBlendEnable = Diligent::True;
    auto &rt0 = bsDesc.RenderTargets[0];
    rt0.BlendEnable = Diligent::True;
    rt0.RenderTargetWriteMask = Diligent::COLOR_MASK_ALL;
    rt0.SrcBlend = Diligent::BLEND_FACTOR_SRC_ALPHA;
    rt0.DestBlend = Diligent::BLEND_FACTOR_INV_SRC_ALPHA;
    rt0.BlendOp = Diligent::BLEND_OPERATION_ADD;
    rt0.SrcBlendAlpha = Diligent::BLEND_FACTOR_SRC_ALPHA;
    rt0.DestBlendAlpha = Diligent::BLEND_FACTOR_INV_SRC_ALPHA;
    rt0.BlendOpAlpha = Diligent::BLEND_OPERATION_ADD;

    psoCreateInfo.GraphicsPipeline.BlendDesc = bsDesc;

    Diligent::LayoutElement layoutElems[] = {
        // Attribute 0 - vertex position
        Diligent::LayoutElement{0, 0, 4, Diligent::VT_FLOAT32, Diligent::False},
        // Attribute 1 - vertex color
        Diligent::LayoutElement{1, 0, 4, Diligent::VT_FLOAT32, Diligent::False}};
    psoCreateInfo.GraphicsPipeline.InputLayout.LayoutElements = layoutElems;
    psoCreateInfo.GraphicsPipeline.InputLayout.NumElements = _countof(layoutElems);

    LOG_CORE_TRACE("Create Shaders");
    Diligent::ShaderCreateInfo shaderCi;
    // Tell the system that the shader source code is in HLSL.
    // For OpenGL, the engine will convert this into GLSL under the hood
    shaderCi.SourceLanguage = Diligent::SHADER_SOURCE_LANGUAGE_HLSL;

    // Create a vertex shader
    Diligent::RefCntAutoPtr<Diligent::IShader> pVs;
    {
        shaderCi.Desc.ShaderType = Diligent::SHADER_TYPE_VERTEX;
        shaderCi.EntryPoint = "main";
        shaderCi.Desc.Name = "Triangle vertex shader";
        shaderCi.Source = vsSource;
        Application::Get()->GetDevice().GetNative()->CreateShader(shaderCi, &pVs);
    }

    // Create a pixel shader
    Diligent::RefCntAutoPtr<Diligent::IShader> pPs;
    {
        shaderCi.Desc.ShaderType = Diligent::SHADER_TYPE_PIXEL;
        shaderCi.EntryPoint = "main";
        shaderCi.Desc.Name = "Triangle pixel shader";
        shaderCi.Source = psSource;
        Application::Get()->GetDevice().GetNative()->CreateShader(shaderCi, &pPs);
    }

    // Finally, create the pipeline state
    psoCreateInfo.pVS = pVs;
    psoCreateInfo.pPS = pPs;

    // Define variable type that will be used by default
    psoCreateInfo.PSODesc.ResourceLayout.DefaultVariableType = Diligent::SHADER_RESOURCE_VARIABLE_TYPE_STATIC;

    Application::Get()->GetDevice().GetNative()->CreateGraphicsPipelineState(psoCreateInfo, &m_pPso);

    // Since we did not explicitly specify the type for 'Constants' variable, default
    // type (SHADER_RESOURCE_VARIABLE_TYPE_STATIC) will be used. Static variables never
    // change and are bound directly through the pipeline state object.
    if (auto *temp = m_pPso->GetStaticVariableByName(Diligent::SHADER_TYPE_VERTEX, "Constants"))
        temp->Set(m_vsConstants);

    // Create a shader resource binding object and bind all static resources in it
    m_pPso->CreateShaderResourceBinding(&m_pSrb, true);
}

auto __XXECS::Renderer::ThreadUpdate() -> void
{
    // Handle events from the main thread.
    while (true)
    {
        const std::any ev = Application::Get()->GetEventManager().Pop();
        if (!ev.has_value())
            break;

        if (ev.type() == typeid(Event::ResizeEvent))
        {
            const auto [width, height] = any_cast<Event::ResizeEvent>(ev);

            Application::Get()->GetSwapChain().GetNative()->Resize(width, height);
        }
        else if (ev.type() == typeid(Event::ExitEvent))
        {
            Application::Get()->Close();
        }

        Application::Get()->GetImGuiManager().Event(ev);
        Application::Get()->Event(ev);
    }

    Application::Get()->GetImGuiManager().NewFrame();

    auto &pImmediateContext = Application::Get()->GetImmediateContext().GetNative();

    // Set render targets before issuing any draw command.
    // Note that Present() unbinds the back buffer if it is set as render target.
    auto *pRtv = Application::Get()->GetSwapChain().GetNative()->GetCurrentBackBufferRTV();
    auto *pDsv = Application::Get()->GetSwapChain().GetNative()->GetDepthBufferDSV();
    pImmediateContext->SetRenderTargets(1, &pRtv, pDsv, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

    // Let the engine perform required state transitions
    pImmediateContext->ClearRenderTarget(pRtv, Application::Get()->GetClearColor(),
                                         Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
    pImmediateContext->ClearDepthStencil(pDsv, Diligent::CLEAR_DEPTH_FLAG, 1.f, 0,
                                         Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

    Application::Get()->Update();

    Application::Get()->ImGui();

    // Set the pipeline state in the immediate context
    pImmediateContext->SetPipelineState(m_pPso);
    pImmediateContext->CommitShaderResources(m_pSrb, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

    Application::Get()->Render();

    Application::Get()->GetImGuiManager().Render();

    Application::Get()->GetSwapChain().Present();
}

auto __XXECS::Renderer::ThreadExit() -> void
{
    Application::Get()->Shutdown();
}
