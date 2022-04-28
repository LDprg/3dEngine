#include "pch.hpp"
#include "Application.h"

__XXECS::Application* __XXECS::Application::s_Instance = nullptr;

__XXECS::Application::Application()
{
	LOG_CORE_ASSERT(!s_Instance, "Application already exists!");
	s_Instance = this;

	m_Window = std::unique_ptr<Window>();
}

__XXECS::Application::~Application()
{
}

void __XXECS::Application::RunLoop()
{
	while (m_Running)
	{
		m_Window->Update();
		this->Update();
	}
}
