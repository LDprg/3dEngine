/*****************************************************************/ /**
 * \file   Application.cpp
 * \brief  Application source
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#include "Application.hpp"

using namespace XXECS;

Application *Application::m_instance;

Application::Application()
{
    Log::CoreAssert(!m_instance, "Application already exists!");
    m_instance = this;

    m_eventManager = std::make_unique<Event::EventManager>();
    m_window = std::make_unique<Window>();
    m_swapChain = std::make_unique<SwapChain>();
    m_device = std::make_unique<Device>();
    m_immediateContext = std::make_unique<ImmediateContext>();
    m_imGui = std::make_unique<ImGuiManager>();
    m_renderer = std::make_unique<Renderer>();
    m_entityManager = std::make_unique<Entity::EntityManager>();
}

auto Application::RunLoop() -> void
{
    m_window->Init();

    m_renderThread = std::thread([this]
    {
        RunThread();
    });

    while (IsRunning())
        m_window->Update();

    m_window->Close();

    m_renderThread.detach();
}

auto Application::RunThread() -> void
{
    m_renderer->Init();
    m_imGui->Init();
    Init();

    m_timer.Restart();

    while (IsRunning())
    {
        while (true)
        {
            const std::any ev = m_eventManager->Pop();
            if (!ev.has_value())
                break;

            if (const auto resizeEvent = any_cast<Event::ResizeEvent>(&ev))
                m_swapChain->GetNative()->Resize(resizeEvent->width, resizeEvent->height);
            else if (any_cast<Event::ExitEvent>(&ev))
                Close();

            m_imGui->Event(ev);
            Event(ev);
        }

        m_imGui->NewFrame();

        Update(static_cast<float>(m_frameTime.count()) / 1000000.f);

        ImGui();

        m_renderer->Update();

        Render();

        m_imGui->Render();

        m_swapChain->Present();

        m_frameTime = m_timer.Duration();
        m_timer.Restart();
    }

    Shutdown();
}
