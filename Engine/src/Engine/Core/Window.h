#pragma once

#include <Engine/Core/Log.h>
#include <Engine/Renderer/Renderer.h>
#include <GLFW/glfw3.h>

namespace __XXECS
{
	class Window final
	{
	public:
		Window() = default;

		~Window() = default;

		void Init();
		void Close();

		void Update();

		void SetFullscreen(bool fullscreen);

		bool IsFullscreen() const
		{
			return m_isFullscreen;
		}

		RenderArguments GetRenderArgs();

		GLFWwindow* GetNativeWindow() const
		{
			return m_window;
		}

		std::pair<float, float> GetSize();
		float GetWidth();
		float GetHeight();

		std::pair<float, float> GetPos() const;
		float GetPosX() const;
		float GetPosY() const;

	private:
		GLFWwindow* m_window = nullptr;
		static bool m_hasBeenInit;
		bool m_isFullscreen = false;
		int m_width = 0;
		int m_height = 0;

		float m_oldWidth = 0;
		float m_oldHeight = 0;
		float m_oldPosX = 0;
		float m_oldPosY = 0;
	};
}
