/*****************************************************************/ /**
 * \file   Window.cpp
 * \brief  Windows source
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#include "Window.hpp"

#include "Application.hpp"
#include "Engine/Events/Event.hpp"

using namespace XXECS;

bool Window::m_hasBeenInit = false;

auto Window::GlfwErrorCallback(int error, const char *description) -> void
{
    Log::CoreError("GLFW Error ({0}): {1}", error, description);
}

auto Window::GlfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) -> void
{
    Event::KeyEvent keyEvent{};
    keyEvent.key = static_cast<Key>(key);
    keyEvent.action = static_cast<Action>(action);
    Application::Get()->GetEventManager().Push(keyEvent);
}

auto Window::GlfwCursorPositionCallback(GLFWwindow *window, double xpos, double ypos) -> void
{
    Event::MouseMovedEvent movedEvent{};
    movedEvent.x = static_cast<int>(xpos);
    movedEvent.y = static_cast<int>(ypos);
    Application::Get()->GetEventManager().Push(movedEvent);
}

auto Window::GlfwMouseButtonCallback(GLFWwindow *window, int button, int action, int mods) -> void
{
    Event::KeyEvent keyEvent{};
    keyEvent.key = static_cast<Key>(button);
    keyEvent.action = static_cast<Action>(action);
    Application::Get()->GetEventManager().Push(keyEvent);
}

auto Window::GlfwSetFramebufferSizeCallback(GLFWwindow *window, int width, int height) -> void
{
    Event::ResizeEvent resizeEvent{};
    resizeEvent.width = width;
    resizeEvent.height = height;
    Application::Get()->GetEventManager().Push(resizeEvent);
}

auto Window::Init() -> void
{
    if (!m_hasBeenInit)
    {
        glfwSetErrorCallback(GlfwErrorCallback);

        Log::CoreAssert(glfwInit(), "Could not initialize GLFW!");

#if ENGINE_PLATFORM_WINDOWS
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#else
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

        m_hasBeenInit = true;
    }

    m_window = glfwCreateWindow(1024, 768, "hello world", nullptr, nullptr);

    auto [width, height] = GetSize();
    m_oldHeight = height;
    m_oldWidth = width;

    auto [posX, posY] = GetPos();
    m_oldPosX = posX;
    m_oldPosY = posY;

    Log::CoreAssert(m_window, "Could not initialize Window!");

    glfwSetKeyCallback(m_window, GlfwKeyCallback);
    glfwSetCursorPosCallback(m_window, GlfwCursorPositionCallback);
    glfwSetMouseButtonCallback(m_window, GlfwMouseButtonCallback);
    glfwSetFramebufferSizeCallback(m_window, GlfwSetFramebufferSizeCallback);
}

auto Window::Close() const -> void
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

auto Window::Update() const -> void
{
    glfwWaitEvents();

    if (glfwWindowShouldClose(m_window))
        Application::Get()->Close();
}

auto Window::SetFullscreen(const bool fullscreen) -> void
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

            const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
            glfwSetWindowMonitor(m_window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);

            m_isFullscreen = true;
        }
    }
    else if (m_isFullscreen)
    {
        glfwSetWindowMonitor(m_window, nullptr, static_cast<int>(m_oldPosX), static_cast<int>(m_oldPosY),
                             static_cast<int>(m_oldWidth), static_cast<int>(m_oldHeight), 0);
        m_isFullscreen = false;
    }
}

auto Window::GetSize() -> std::pair<float, float>
{
    int width, height;

    glfwGetWindowSize(m_window, &width, &height);

    m_width = width;
    m_height = height;

    return {static_cast<float>(width), static_cast<float>(height)};
}

auto Window::GetWidth() -> float
{
    auto [width, height] = GetSize();
    return width;
}

auto Window::GetHeight() -> float
{
    auto [width, height] = GetSize();
    return height;
}

auto Window::GetPos() const -> std::pair<float, float>
{
    int x, y;

    glfwGetWindowPos(m_window, &x, &y);

    return {static_cast<float>(x), static_cast<float>(y)};
}

auto Window::GetPosX() const -> float
{
    auto [x, y] = GetPos();
    return x;
}

auto Window::GetPosY() const -> float
{
    auto [x, y] = GetPos();
    return y;
}
