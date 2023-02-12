#include "Application.h"

__XXECS::Application* __XXECS::Application::m_Instance = nullptr;

__XXECS::Application::Application()
{
	LOG_CORE_ASSERT(!m_Instance, "Application already exists!");
	m_Instance = this;

	m_EventManager = new EventManager();
	m_Window = new Window();
	m_SwapChain = new SwapChain();
	m_Device = new Device();
	m_ImmediateContext = new ImmediateContext();
	m_ImGui = new ImguiManager();
	m_Renderer = new Renderer();
	m_EntityManager = new EntityManager();
}

void __XXECS::Application::RunLoop()
{
	m_Window->Init();
	m_Renderer->Bind(m_Window->GetRenderArgs());

	while (IsRunning())
		m_Window->Update();

	m_Window->Close();
	m_Renderer->Exit();
}
