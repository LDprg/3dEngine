#pragma once

#include "Log.h"

#include <GLFW/glfw3.h>
#if BX_PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#elif BX_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elif BX_PLATFORM_OSX
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#include <GLFW/glfw3native.h>

static void glfw_errorCallback(int error, const char* description)
{
	LOG_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

namespace __XXECS
{
	class Window
	{
	public:
		Window(){
			glfwSetErrorCallback(glfw_errorCallback);

			LOG_CORE_ASSERT(glfwInit(), "Could not initialize GLFW!");

			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

			m_window = glfwCreateWindow(1024, 768, "helloworld multithreaded", nullptr, nullptr);
			
			LOG_CORE_ASSERT(m_window , "Could not initialize Window!");
		}
		
		~Window(){
			glfwTerminate();
		}

		void Update()
		{
			glfwPollEvents();
		}

	private:
		GLFWwindow* m_window;
	};
}