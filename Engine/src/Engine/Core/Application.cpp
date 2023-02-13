#include "Application.hpp"

__XXECS::Application* __XXECS::Application::m_Instance;

__XXECS::Application::Application()
{
	LOG_CORE_ASSERT(!m_Instance, "Application already exists!");
	m_Instance = this;

	m_EventManager = std::make_unique<EventManager>();
	m_Window = std::make_unique<Window>();
	m_SwapChain = std::make_unique<SwapChain>();
	m_Device = std::make_unique<Device>();
	m_ImmediateContext = std::make_unique<ImmediateContext>();
	m_ImGui = std::make_unique<ImGuiManager>();
	m_Renderer = std::make_unique<Renderer>();
	m_EntityManager = std::make_unique<EntityManager>();
}

void __XXECS::Application::RunLoop() const
{
	m_Window->Init();
	m_Renderer->Bind(m_Window->GetRenderArgs());

	while (IsRunning())
		m_Window->Update();

	m_Window->Close();
	m_Renderer->Exit();
}
