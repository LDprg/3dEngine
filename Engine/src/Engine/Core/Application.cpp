#include "pch.hpp"
#include "Application.h"

__XXECS::Application* __XXECS::Application::s_Instance = nullptr;

__XXECS::Application::Application()
{
	LOG_CORE_ASSERT(!s_Instance, "Application already exists!");
	s_Instance = this;

	m_EventManager = new EventManager();
	m_Window = new Window();
	m_Renderer = new Renderer();
}

__XXECS::Application::~Application()
{
}

void __XXECS::Application::RunLoop()
{
	m_Window->Init();
	m_Renderer->Init();
	m_Renderer->Bind(m_Window->GetRenderArgs());
	Get().InitMain();

	while (m_Running)
	{
		m_Window->Update();
		Get().UpdateMain();
		m_Renderer->Update();
	}

	Get().ShutdownMain();
	m_Renderer->Exit();
	m_Window->Close();
}
