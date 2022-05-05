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

		void setFullscreen(bool fullscreen);
		bool isFullscreen() { return m_isFullscreen; }

		RenderArguments GetRenderArgs();
		GLFWwindow* GetNativeWindow() { return m_window; }

		std::pair<int, int> GetSize();
		float GetWidth();
		float GetHeight();

		std::pair<int, int> GetPos();
		float GetPosX();
		float GetPosY();

	private:
		GLFWwindow* m_window;
		static bool s_hasBeenInit;
		bool m_isFullscreen = false;
		int m_width;
		int m_height;

		int m_oldWidth;
		int m_oldHeight;
		int m_oldPosX;
		int m_oldPosY;
	};
}
