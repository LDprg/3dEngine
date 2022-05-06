#include <ImGuiDiligentRenderer.hpp>

#include "pch.hpp"

#include <ThirdParty/imgui/backends/imgui_impl_glfw.h>

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
{/*
	ThreadInit(userData);

	while (Application::Get().IsRunning())
		ThreadUpdate();

	ThreadExit();*/
	return 0;
}


void __XXECS::Renderer::ThreadInit(const RenderArguments* args)
{
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	
	ImGui_ImplGlfw_InitForOther(Application::Get().GetWindow().GetNativeWindow(), true);

	Application::Get().Init();
}

void __XXECS::Renderer::ThreadUpdate()
{
	// Handle events from the main thread.
	while (const auto ev = static_cast<EventType*>(Application::Get().GetEventManager().Pop()))
	{
		if (*ev == EventType::Resize)
		{
			//const auto resizeEvent = reinterpret_cast<ResizeEvent*>(ev);

		}
		else if (*ev == EventType::Exit)
			Application::Get().Close();

		Application::Get().Event(ev);

		delete ev;
	}
	
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	Application::Get().UpdateImGui();

	ImGui::Render();

	Application::Get().Update();
}

void __XXECS::Renderer::ThreadExit()
{
	Application::Get().Shutdown();
	
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
