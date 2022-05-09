#pragma once

#include <Engine/Core/Window.h>
#include <Engine/Events/Event.h>
#include <Engine/Renderer/imgui.h>

#include "Engine/Renderer/Device.h"
#include "Engine/Renderer/ImmediateContext.h"

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
		virtual void UpdateImGui() = 0;
		virtual void Update() = 0;
		virtual void Shutdown() = 0;

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

		ImguiManager& GetImguiManager() const
		{
			return *m_imgui;
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

	private:
		static Application* m_instance;
	};
}
