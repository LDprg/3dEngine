#include "Window.h"
#include "pch.hpp"

#if BX_PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#elif BX_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elif BX_PLATFORM_OSX
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#include <GLFW/glfw3native.h>

#include "Engine/Events/Event.h"

bool __XXECS::Window::m_hasBeenInit = false;

static void GlfwErrorCallback(int error, const char* description)
{
	LOG_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

static void GlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	const auto keyEvent = new __XXECS::KeyEvent;
	keyEvent->key = static_cast<Key>(key);
	keyEvent->action = static_cast<Action>(action);
	__XXECS::Application::Get().GetEventManager().Push(keyEvent);
}

void __XXECS::Window::Init()
{
	if (!m_hasBeenInit)
	{
		glfwSetErrorCallback(GlfwErrorCallback);

		LOG_CORE_ASSERT(glfwInit(), "Could not initialize GLFW!");

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		m_hasBeenInit = true;
	}

	m_window = glfwCreateWindow(1024, 768, "helloworld", nullptr, nullptr);

	auto [width, height] = GetSize();
	m_oldHeight = height;
	m_oldWidth = width;

	auto [posX, posY] = GetPos();
	m_oldPosX = posX;
	m_oldPosY = posY;

	LOG_CORE_ASSERT(m_window, "Could not initialize Window!");

	//glfwSetKeyCallback(m_window, GlfwKeyCallback);
	//glfwSetWindowSizeCallback(m_window, glfw_ResizeCallback);
}

void __XXECS::Window::Close()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void __XXECS::Window::Update()
{
	glfwWaitEvents();

	if (glfwWindowShouldClose(m_window))
		Application::Get().Close();

	// Send window resize event to the API thread.
	const int oldWidth = m_width;
	const int oldHeight = m_height;
	glfwGetWindowSize(m_window, &m_width, &m_height);
	if (m_width != oldWidth || m_height != oldHeight)
	{
		const auto resize = new ResizeEvent;
		resize->width = m_width;
		resize->height = m_height;
		Application::Get().GetEventManager().Push(resize);
	}
}

void __XXECS::Window::SetFullscreen(const bool fullscreen)
{
	if (fullscreen)
	{
		if (!m_isFullscreen)
		{
			auto [width, height] = GetSize();
			m_oldHeight = height;
			m_oldWidth = width;

			auto [posX, posY] = GetPos();
			m_oldPosX = posX;
			m_oldPosY = posY;

			const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
			glfwSetWindowMonitor(m_window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);

			m_isFullscreen = true;
		}
	}
	else if (m_isFullscreen)
	{
		glfwSetWindowMonitor(m_window, nullptr, static_cast<int>(m_oldPosX), static_cast<int>(m_oldPosY), static_cast<int>(m_oldWidth), static_cast<int>(m_oldHeight), 0);
		m_isFullscreen = false;
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
	glfwGetWindowSize(m_window, &m_width, &m_height);
	renderArgs.width = static_cast<uint32_t>(m_width);
	renderArgs.height = static_cast<uint32_t>(m_height);

	return renderArgs;
}

std::pair<float, float> __XXECS::Window::GetSize()
{
	int width, height;

	glfwGetWindowSize(m_window, &width, &height);

	m_width = width;
	m_height = height;

	return {static_cast<float>(width), static_cast<float>(height)};
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

std::pair<float, float> __XXECS::Window::GetPos() const
{
	int x, y;

	glfwGetWindowPos(m_window, &x, &y);

	return { static_cast<float>(x), static_cast<float>(y)};
}

float __XXECS::Window::GetPosX() const
{
	auto [x, y] = GetPos();
	return x;
}

float __XXECS::Window::GetPosY() const
{
	auto [x, y] = GetPos();
	return y;
}
