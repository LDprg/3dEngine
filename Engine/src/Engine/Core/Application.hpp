/*****************************************************************/ /**
 * \file   Application.hpp
 * \brief  Application class, the base class for main applications
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

#include "Engine/Core/Window.hpp"
#include "Engine/Entity/EntityManager.hpp"
#include "Engine/Events/Event.hpp"
#include "Engine/Renderer/Device.hpp"
#include "Engine/Renderer/imgui.hpp"
#include "Engine/Renderer/ImmediateContext.hpp"
#include "Engine/Renderer/Renderer.hpp"
#include "Engine/Renderer/SwapChain.hpp"

#include "Engine/Math/Vector.hpp"

auto main() -> int;

namespace __XXECS
{

    class Application
    {
        friend auto ::main() -> int;

    public:
        Application();
        virtual ~Application() = default;
        Application(const Application &) = delete;
        Application(const Application &&) = delete;
        auto operator=(const Application &) -> void = delete;
        auto operator=(const Application &&) -> void = delete;

        /**
         * \brief Is called when an event is fired
         * \param event std::any of fired event
         */
        virtual auto Event(const std::any &event) -> void = 0;

        /**
         * \brief Is called to initialize the application
         */
        virtual auto Init() -> void = 0;

        /**
         * \brief Is called to update the application
         */
        virtual auto Update() -> void = 0;

        /**
         * \brief Is called to render the application
         */
        virtual auto Render() -> void = 0;

        /**
         * \brief Is called when the application is closed
         */
        virtual auto Shutdown() -> void = 0;

        /**
         * \brief Should update ImGui
         */
        virtual auto ImGui() -> void
        {
        }

        /**
         * \brief Get the running state of the application
         * \return Running state
         */
        [[nodiscard]] auto IsRunning() const -> bool
        {
            return m_running;
        }

        /**
         * \brief Close the application
         */
        auto Close() -> void
        {
            m_running = false;
        }

        /**
         * \brief Get the instance of the singleton application
         * \return instance of the application
         */
        static auto Get() -> Application*
        {
            return m_instance;
        }

        /**
         * \brief Get the window reference
         * \return Window reference
         */
        [[nodiscard]] auto GetWindow() const -> Window&
        {
            return *m_window;
        }

        /**
         * \brief Get the event manager reference
         * \return EventManager reference
         */
        [[nodiscard]] auto GetEventManager() const -> Event::EventManager&
        {
            return *m_eventManager;
        }

        /**
         * \brief Get the renderer reference
         * \return Renderer reference
         */
        [[nodiscard]] auto GetRenderer() const -> Renderer&
        {
            return *m_renderer;
        }

        /**
         * \brief Get the swap chain reference
         * \return SwapChain reference
         */
        [[nodiscard]] auto GetSwapChain() const -> SwapChain&
        {
            return *m_swapChain;
        }

        /**
         * \brief Get the device reference
         * \return Device reference
         */
        [[nodiscard]] auto GetDevice() const -> Device&
        {
            return *m_device;
        }

        /**
         * \brief Get the immediate context reference
         * \return ImmediateContext reference
         */
        [[nodiscard]] auto GetImmediateContext() const -> ImmediateContext&
        {
            return *m_immediateContext;
        }

        /**
         * \brief Get the ImGui manager reference
         * \return ImGuiManager reference
         */
        [[nodiscard]] auto GetImGuiManager() const -> ImGuiManager&
        {
            return *m_imGui;
        }

        /**
         * \brief Get the entity manager reference
         * \return Entity Manager reference
         */
        [[nodiscard]] auto GetEntityManager() const -> EntityManager&
        {
            return *m_entityManager;
        }

        /**
         * \brief Get the background color reference
         * \return Background color reference
         */
        auto GetClearColor() -> Math::Color&
        {
            return m_clearColor;
        }

    private:
        /**
         * \brief main thread loop
         */
        auto RunLoop() const -> void;

        bool m_running = true;
        Math::Color m_clearColor = {1.f, 1.f, 1.f};

        std::unique_ptr<Window> m_window;
        std::unique_ptr<Event::EventManager> m_eventManager;
        std::unique_ptr<Renderer> m_renderer;
        std::unique_ptr<SwapChain> m_swapChain;
        std::unique_ptr<Device> m_device;
        std::unique_ptr<ImmediateContext> m_immediateContext;
        std::unique_ptr<ImGuiManager> m_imGui;
        std::unique_ptr<EntityManager> m_entityManager;

        static Application *m_instance;
    };
}
