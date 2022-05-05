#include "pch.hpp"
#include "Window.h"

#if BX_PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#elif BX_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elif BX_PLATFORM_OSX
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#include <GLFW/glfw3native.h>

#include "Engine/Events/Event.h"

static void glfw_errorCallback(int error, const char* description)
{
	LOG_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

static void glfw_keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	auto keyEvent = new __XXECS::KeyEvent;
	keyEvent->key = key;
	keyEvent->action = action;
	__XXECS::Application::Get().GetEventManager().push(keyEvent);
}


void __XXECS::Window::Init()
{
	if (!hasBeenInit)
	{
		glfwSetErrorCallback(glfw_errorCallback);

		LOG_CORE_ASSERT(glfwInit(), "Could not initialize GLFW!");

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		hasBeenInit = true;
	}

	m_window = glfwCreateWindow(1024, 768, "helloworld multithreaded", nullptr, nullptr);

	LOG_CORE_ASSERT(m_window, "Could not initialize Window!");

	glfwSetKeyCallback(m_window, glfw_keyCallback);
}

void __XXECS::Window::Close()
{
	glfwTerminate();
}

void __XXECS::Window::Update()
{
	glfwWaitEvents();

	if (glfwWindowShouldClose(m_window))
	{
		Application::Get().Close();
	}

	// Send window resize event to the API thread.
	int oldWidth = width, oldHeight = height;
	glfwGetWindowSize(m_window, &width, &height);
	if (width != oldWidth || height != oldHeight)
	{
		auto resize = new ResizeEvent;
		resize->width = static_cast<uint32_t>(width);
		resize->height = static_cast<uint32_t>(height);
		Application::Get().GetEventManager().push(resize);
	}
}

__XXECS::RenderArguments __XXECS::Window::GetRenderArgs()
{
	RenderArguments renderArgs;

#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
	renderArgs.platformData.ndt = glfwGetX11Display();
	renderArgs.platformData.nwh = (void*)(uintptr_t)glfwGetX11Window(m_window);
#elif BX_PLATFORM_OSX
	renderArgs.platformData.nwh = glfwGetCocoaWindow(m_window);
#elif BX_PLATFORM_WINDOWS
	renderArgs.platformData.nwh = glfwGetWin32Window(m_window);
#endif
	glfwGetWindowSize(m_window, &width, &height);
	renderArgs.width = static_cast<uint32_t>(width);
	renderArgs.height = static_cast<uint32_t>(height);

	return renderArgs;
}

std::pair<float, float> __XXECS::Window::GetSize()
{
	auto window = Application::Get().GetWindow().GetNativeWindow();
	int width, height;

	glfwGetWindowSize(window, &width, &height);

	return { static_cast<float>(width), static_cast<float>(height) };
}

float __XXECS::Window::GetWidth()
{
	auto [width, height] = GetSize();
	return width;
}

float __XXECS::Window::GetHeight()
{
	auto [width, height] = GetSize();
	return height;
}