#pragma once

#include <Engine/Core/Window.h>
#include <Engine/Events/Event.h>
#include <Engine/Renderer/imgui.h>

#include "Engine/Entity/EntityManager.h"
#include "Engine/Renderer/Device.h"
#include "Engine/Renderer/ImmediateContext.h"

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

		virtual void Event(EventType* event) = 0;

		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void Shutdown() = 0;

		virtual void ImGui()
		{
		}


		bool IsRunning() const
		{
			return m_running;
		}

		void Close()
		{
			m_running = false;
		}

		static Application& Get()
		{
			return *m_instance;
		}

		Window& GetWindow() const
		{
			return *m_window;
		}

		EventManager& GetEventManager() const
		{
			return *m_eventManager;
		}

		Renderer& GetRenderer() const
		{
			return *m_renderer;
		}

		SwapChain& GetSwapChain() const
		{
			return *m_SwapChain;
		}

		Device& GetDevice() const
		{
			return *m_device;
		}

		ImmediateContext& GetImmediateContext() const
		{
			return *m_ImmediateContext;
		}

		ImguiManager& GetImGuiManager() const
		{
			return *m_imgui;
		}

		EntityManager& GetEntityManager() const
		{
			return *m_entityManager;
		}

		Color<float>& GetClearColor()
		{
			return m_clearColor;
		}

	private:
		void RunLoop();

		bool m_running = true;
		Window* m_window;
		EventManager* m_eventManager;
		Renderer* m_renderer;
		SwapChain* m_SwapChain;
		Device* m_device;
		ImmediateContext* m_ImmediateContext;
		ImguiManager* m_imgui;
		EntityManager* m_entityManager;
		Color<float> m_clearColor = {1.f, 1.f, 1.f, 1.f};

		static Application* m_instance;
	};
}
