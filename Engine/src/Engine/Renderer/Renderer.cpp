#include "pch.hpp"

#include "Engine/Renderer/imgui/imgui_impl_bgfx.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>

bgfx::ShaderHandle __XXECS::Renderer::LoadShader(const char* filename)
{
	auto shaderPath = "???";

	switch (bgfx::getRendererType())
	{
	case bgfx::RendererType::Noop:
	case bgfx::RendererType::Direct3D9:
		shaderPath = "shaders/dx9/";
		break;
	case bgfx::RendererType::Direct3D11:
	case bgfx::RendererType::Direct3D12:
		shaderPath = "shaders/dx11/";
		break;
	case bgfx::RendererType::Gnm:
		shaderPath = "shaders/pssl/";
		break;
	case bgfx::RendererType::Metal:
		shaderPath = "shaders/metal/";
		break;
	case bgfx::RendererType::OpenGL:
		shaderPath = "shaders/glsl/";
		break;
	case bgfx::RendererType::OpenGLES:
		shaderPath = "shaders/essl/";
		break;
	case bgfx::RendererType::Vulkan:
		shaderPath = "shaders/spirv/";
		break;
	default: ;
	}

	const size_t shaderLen = strlen(shaderPath);
	const size_t fileLen = strlen(filename);
	const auto filePath = static_cast<char*>(malloc(shaderLen + fileLen + 1 + 1));
	strcpy(filePath, shaderPath);
	strcpy(&filePath[shaderLen], filename);

	FILE* file = fopen(filename, "rb");
	fseek(file, 0, SEEK_END);
	const long fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	const bgfx::Memory* mem = bgfx::alloc(fileSize + 1);
	fread(mem->data, 1, fileSize, file);
	mem->data[mem->size - 1] = '\0';
	fclose(file);

	return createShader(mem);
}

void __XXECS::Renderer::Exit() { m_renderThread.shutdown(); }

void __XXECS::Renderer::Bind(const RenderArguments renderArgs)
{
	m_renderArgs = renderArgs;
	m_renderThread.init(RunThread, &m_renderArgs);
}

int32_t __XXECS::Renderer::RunThread(bx::Thread* self, void* userData)
{
	ThreadInit(static_cast<RenderArguments*>(userData));

	while (Application::Get().IsRunning())
		ThreadUpdate();

	ThreadExit();
	return 0;
}


void __XXECS::Renderer::ThreadInit(const RenderArguments* args)
{
	// Initialize bgfx using the native window handle and window resolution.
	bgfx::Init init;
	init.platformData = args->platformData;
	init.type = bgfx::RendererType::Count;
	init.resolution.width = args->width;
	init.resolution.height = args->height;
	init.resolution.reset = BGFX_RESET_VSYNC | BGFX_RESET_MSAA_X2;
	LOG_CORE_ASSERT(bgfx::init(init), "BGFX INIT FAILED");
	bgfx::setState(BGFX_STATE_MSAA);
	// Set view 0 to the same dimensions as the window and to clear the color buffer.
	bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF);
	setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
	uint32_t width = args->width;
	uint32_t height = args->height;


	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOther(Application::Get().GetWindow().GetNativeWindow(), true);
	ImGui_Implbgfx_Init(255);

	Application::Get().Init();
}

void __XXECS::Renderer::ThreadUpdate()
{
	// Handle events from the main thread.
	while (const auto ev = static_cast<EventType*>(Application::Get().GetEventManager().Pop()))
	{
		if (*ev == EventType::Resize)
		{
			const auto resizeEvent = reinterpret_cast<ResizeEvent*>(ev);
			bgfx::reset(resizeEvent->width, resizeEvent->height, BGFX_RESET_VSYNC | BGFX_RESET_MSAA_X16);
			setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
		}
		else if (*ev == EventType::Exit)
			Application::Get().Close();

		Application::Get().Event(ev);

		delete ev;
	}

	ImGui_Implbgfx_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	Application::Get().UpdateImGui();

	ImGui::Render();
	ImGui_Implbgfx_RenderDrawLists(ImGui::GetDrawData());

	bgfx::touch(kClearView);

	Application::Get().Update();

	bgfx::frame();
}

void __XXECS::Renderer::ThreadExit()
{
	Application::Get().Shutdown();

	ImGui_Implbgfx_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	bgfx::shutdown();
}
