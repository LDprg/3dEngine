#include "pch.hpp"

#include "Engine/Renderer/imgui/imgui_impl_bgfx.h"
#include "imgui/imgui_impl_bgfx.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>

#include "bx/string.h"

void __XXECS::Renderer::Init()
{
	bgfx::renderFrame();
}

void __XXECS::Renderer::Exit()
{
	while (bgfx::RenderFrame::NoContext != bgfx::renderFrame());
	m_renderThread.shutdown();
}

void __XXECS::Renderer::Update()
{
	bgfx::renderFrame();
}

void __XXECS::Renderer::Bind(RenderArguments renderArgs)
{
	m_renderArgs = renderArgs;
	m_renderThread.init(runThread, &m_renderArgs);
}

int32_t __XXECS::Renderer::runThread(bx::Thread* self, void* userData)
{
	auto args = static_cast<RenderArguments*>(userData);
	// Initialize bgfx using the native window handle and window resolution.
	bgfx::Init init;
	init.platformData = args->platformData;
	init.resolution.width = args->width;
	init.resolution.height = args->height;
	init.resolution.reset = BGFX_RESET_VSYNC;
	LOG_CORE_ASSERT(bgfx::init(init), "BGFX INIT FAILED");
	// Set view 0 to the same dimensions as the window and to clear the color buffer.
	const bgfx::ViewId kClearView = 0;
	bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR, 0x443355FF);
	setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
	uint32_t width = args->width;
	uint32_t height = args->height;

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOther(Application::Get().GetWindow().GetNativeWindow(), true);
	ImGui_Implbgfx_Init(kClearView);

	Application::Get().Init();

	while (Application::Get().isRunning())
	{
		// Handle events from the main thread.
		while (auto ev = static_cast<EventType*>(Application::Get().GetEventManager().pop()))
		{
			if (*ev == EventType::Resize)
			{
				auto resizeEvent = (ResizeEvent*)ev;
				bgfx::reset(resizeEvent->width, resizeEvent->height, BGFX_RESET_VSYNC);
				setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
				width = resizeEvent->width;
				height = resizeEvent->height;
			}
			else if (*ev == EventType::Exit)
			{
				Application::Get().Close();
			}

			Application::Get().Event(ev);

			delete ev;
		}

		bgfx::touch(kClearView);

		ImGui_ImplGlfw_NewFrame();
		ImGui_Implbgfx_NewFrame();
		ImGui::NewFrame();

		Application::Get().Update();

		ImGui::Render();
		ImGui_Implbgfx_RenderDrawLists(ImGui::GetDrawData());

		bgfx::frame();
	}

	Application::Get().Shutdown();

	ImGui_Implbgfx_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	bgfx::shutdown();
	return 0;
}
