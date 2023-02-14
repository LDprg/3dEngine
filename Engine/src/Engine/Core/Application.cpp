/*****************************************************************/ /**
 * \file   Application.cpp
 * \brief  Application source
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#include "Application.hpp"

__XXECS::Application *__XXECS::Application::m_instance;

__XXECS::Application::Application()
{
    LOG_CORE_ASSERT(!m_instance, "Application already exists!")
    m_instance = this;

    m_eventManager = std::make_unique<EventManager>();
    m_window = std::make_unique<Window>();
    m_swapChain = std::make_unique<SwapChain>();
    m_device = std::make_unique<Device>();
    m_immediateContext = std::make_unique<ImmediateContext>();
    m_imGui = std::make_unique<ImGuiManager>();
    m_renderer = std::make_unique<Renderer>();
    m_entityManager = std::make_unique<EntityManager>();
}

auto __XXECS::Application::RunLoop() const -> void
{
    m_window->Init();
    m_renderer->Init();

    while (IsRunning())
        m_window->Update();

    m_window->Close();
    m_renderer->Exit();
}
