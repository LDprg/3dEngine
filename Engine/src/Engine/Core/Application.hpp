#pragma once

#include "Engine/Core/Window.hpp"
#include "Engine/Entity/EntityManager.hpp"
#include "Engine/Events/Event.hpp"
#include "Engine/Renderer/Device.hpp"
#include "Engine/Renderer/imgui.hpp"
#include "Engine/Renderer/ImmediateContext.hpp"
#include "Engine/Renderer/SwapChain.hpp"

#include "Engine/Math/Vector.hpp"

auto main(int argc, char** argv) -> int;

namespace __XXECS
{
	class Application
	{
		friend auto ::main(int argc, char** argv) -> int;

	public:
		Application();
		virtual ~Application() = default;
		Application(const Application&) = delete;
		Application(const Application&&) = delete;
		auto operator=(const Application&) -> void = delete;
		auto operator=(const Application&&) -> void = delete;

		virtual auto Event(const std::any& event) -> void = 0;

		virtual auto Init() -> void = 0;
		virtual auto Update() -> void = 0;
		virtual auto Render() -> void = 0;
		virtual auto Shutdown() -> void = 0;

		virtual auto ImGui() -> void
		{
		}

		[[nodiscard]] auto IsRunning() const -> bool
		{
			return m_running;
		}

		auto Close() -> void
		{
			m_running = false;
		}

		static auto Get() -> Application*
		{
			return m_instance;
		}

		[[nodiscard]] auto GetWindow() const -> Window&
		{
			return *m_window;
		}

		[[nodiscard]] auto GetEventManager() const -> EventManager&
		{
			return *m_eventManager;
		}

		[[nodiscard]] auto GetRenderer() const -> Renderer&
		{
			return *m_renderer;
		}

		[[nodiscard]] auto GetSwapChain() const -> SwapChain&
		{
			return *m_swapChain;
		}

		[[nodiscard]] auto GetDevice() const -> Device&
		{
			return *m_device;
		}

		[[nodiscard]] auto GetImmediateContext() const -> ImmediateContext&
		{
			return *m_immediateContext;
		}

		[[nodiscard]] auto GetImGuiManager() const -> ImGuiManager&
		{
			return *m_imGui;
		}

		[[nodiscard]] auto GetEntityManager() const -> EntityManager&
		{
			return *m_entityManager;
		}

		auto GetClearColor() -> Color&
		{
			return m_clearColor;
		}

	private:
		auto RunLoop() const -> void;

		bool m_running = true;
		Color m_clearColor = {1.f, 1.f, 1.f};

		std::unique_ptr<Window> m_window;
		std::unique_ptr<EventManager> m_eventManager;
		std::unique_ptr<Renderer> m_renderer;
		std::unique_ptr<SwapChain> m_swapChain;
		std::unique_ptr<Device> m_device;
		std::unique_ptr<ImmediateContext> m_immediateContext;
		std::unique_ptr<ImGuiManager> m_imGui;
		std::unique_ptr<EntityManager> m_entityManager;

		static Application* m_instance;
	};
}
