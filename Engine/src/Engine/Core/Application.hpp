#pragma once

#include "Engine/Core/Window.hpp"
#include "Engine/Entity/EntityManager.hpp"
#include "Engine/Events/Event.hpp"
#include "Engine/Renderer/Device.hpp"
#include "Engine/Renderer/imgui.hpp"
#include "Engine/Renderer/ImmediateContext.hpp"
#include "Engine/Renderer/SwapChain.hpp"

#include "Engine/Math/Vector.hpp"

int main(int argc, char** argv);

namespace __XXECS
{
	class Application
	{
		friend int ::main(int argc, char** argv);

	public:
		Application();
		virtual ~Application() = default;
		Application(const Application&) = delete;
		void operator=(const Application&) = delete;
		Application(const Application&&) = delete;
		void operator=(const Application&&) = delete;

		virtual void Event(const std::any& event) = 0;

		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void Shutdown() = 0;

		virtual void ImGui()
		{
		}

		[[nodiscard]] bool IsRunning() const
		{
			return m_running;
		}

		void Close()
		{
			m_running = false;
		}

		static Application* Get()
		{
			return m_Instance;
		}

		[[nodiscard]] Window& GetWindow() const
		{
			return *m_Window;
		}

		[[nodiscard]] EventManager& GetEventManager() const
		{
			return *m_EventManager;
		}

		[[nodiscard]] Renderer& GetRenderer() const
		{
			return *m_Renderer;
		}

		[[nodiscard]] SwapChain& GetSwapChain() const
		{
			return *m_SwapChain;
		}

		[[nodiscard]] Device& GetDevice() const
		{
			return *m_Device;
		}

		[[nodiscard]] ImmediateContext& GetImmediateContext() const
		{
			return *m_ImmediateContext;
		}

		[[nodiscard]] ImGuiManager& GetImGuiManager() const
		{
			return *m_ImGui;
		}

		[[nodiscard]] EntityManager& GetEntityManager() const
		{
			return *m_EntityManager;
		}

		Color& GetClearColor()
		{
			return m_clearColor;
		}

	private:
		void RunLoop() const;

		bool m_running = true;
		Color m_clearColor = {1.f, 1.f, 1.f};

		std::unique_ptr<Window> m_Window;
		std::unique_ptr<EventManager> m_EventManager;
		std::unique_ptr<Renderer> m_Renderer;
		std::unique_ptr<SwapChain> m_SwapChain;
		std::unique_ptr<Device> m_Device;
		std::unique_ptr<ImmediateContext> m_ImmediateContext;
		std::unique_ptr<ImGuiManager> m_ImGui;
		std::unique_ptr<EntityManager> m_EntityManager;

		static Application* m_Instance;
	};
}
