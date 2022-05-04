#pragma once

#include "Log.h"

#include <GLFW/glfw3.h>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include "Engine/Renderer/Renderer.h"


namespace __XXECS
{
	class Window
	{
	public:
		Window()
		{
		}

		virtual ~Window()
		{
		}

		void Init();
		void Close();

		void Update();

		RenderArguments GetRenderArgs();
		GLFWwindow* GetNativeWindow() { return m_window; }

		std::pair<float, float> GetSize();
		float GetWidth();
		float GetHeight();

	private:
		GLFWwindow* m_window;
		bool hasBeenInit = false;
		int width;
		int height;
	};
}
