#include "Application.h"

__XXECS::Application* __XXECS::Application::m_instance = nullptr;

__XXECS::Application::Application()
{
	LOG_CORE_ASSERT(!m_instance, "Application already exists!");
	m_instance = this;

	m_eventManager = new EventManager();
	m_window = new Window();
	m_renderer = new Renderer();
}

__XXECS::Application::~Application()
= default;

void __XXECS::Application::RunLoop()
{
	m_window->Init();
	m_renderer->Bind(m_window->GetRenderArgs());

	while (IsRunning())
		m_window->Update();

	m_window->Close();
	m_renderer->Exit();
}
