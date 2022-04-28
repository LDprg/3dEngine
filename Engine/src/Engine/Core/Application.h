#pragma once

#include "Window.h"

int main(int argc, char** argv);

namespace __XXECS
{
	class Application
	{
		friend int ::main(int argc, char** argv);
	public:
		Application();
		virtual ~Application();

		virtual void Update() = 0;

		inline static Application& Get() { return *s_Instance; }

	private:
		void RunLoop();

		bool m_Running = true;
		std::unique_ptr<Window> m_Window;

	private:
		static Application* s_Instance;
	};
}