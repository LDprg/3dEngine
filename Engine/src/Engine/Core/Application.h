#pragma once

#include "Window.h"
#include "Engine/Events/Event.h"
#include "Engine/Events/Input.h"

int main(int argc, char** argv);

namespace __XXECS
{
	class Application
	{
		friend int ::main(int argc, char** argv);
	public:
		Application();
		virtual ~Application();

		virtual void Event(EventType* event) = 0;

		virtual void Init() = 0;
		virtual void UpdateImGui() = 0;
		virtual void Update() = 0;
		virtual void Shutdown() = 0;

		bool isRunning() { return m_Running; }
		void Close() { m_Running = false; }

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() { return *m_Window; }
		EventManager& GetEventManager() { return *m_EventManager; }

	private:
		void RunLoop();

		bool m_Running = true;
		Window* m_Window;
		EventManager* m_EventManager;
		Renderer* m_Renderer;

	private:
		static Application* s_Instance;
	};
}
