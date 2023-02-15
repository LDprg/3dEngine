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

bool __XXECS::Window::m_hasBeenInit = false;

auto GlfwErrorCallback(int error, const char *description) -> void
{
    LOG_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

auto GlfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) -> void
{
    __XXECS::Event::KeyEvent keyEvent{};
    keyEvent.key = static_cast<__XXECS::Key>(key);
    keyEvent.action = static_cast<__XXECS::Action>(action);
    __XXECS::Application::Get()->GetEventManager().Push(keyEvent);
}

auto GlfwCursorPositionCallback(GLFWwindow *window, double xpos, double ypos) -> void
{
    __XXECS::Event::MouseMovedEvent movedEvent{};
    movedEvent.x = static_cast<int>(xpos);
    movedEvent.y = static_cast<int>(ypos);
    __XXECS::Application::Get()->GetEventManager().Push(movedEvent);
}

auto GlfwMouseButtonCallback(GLFWwindow *window, int button, int action, int mods) -> void
{
    __XXECS::Event::KeyEvent keyEvent{};
    keyEvent.key = static_cast<__XXECS::Key>(button);
    keyEvent.action = static_cast<__XXECS::Action>(action);
    __XXECS::Application::Get()->GetEventManager().Push(keyEvent);
}

auto GlfwSetFramebufferSizeCallback(GLFWwindow *window, int width, int height) -> void
{
    __XXECS::Event::ResizeEvent resizeEvent{};
    resizeEvent.width = width;
    resizeEvent.height = height;
    __XXECS::Application::Get()->GetEventManager().Push(resizeEvent);
}

auto __XXECS::Window::Init() -> void
{
    if (!m_hasBeenInit)
    {
        glfwSetErrorCallback(GlfwErrorCallback);

        LOG_CORE_ASSERT(glfwInit(), "Could not initialize GLFW!")

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

    LOG_CORE_ASSERT(m_window, "Could not initialize Window!")

    glfwSetKeyCallback(m_window, GlfwKeyCallback);
    glfwSetCursorPosCallback(m_window, GlfwCursorPositionCallback);
    glfwSetMouseButtonCallback(m_window, GlfwMouseButtonCallback);
    glfwSetFramebufferSizeCallback(m_window, GlfwSetFramebufferSizeCallback);
}

auto __XXECS::Window::Close() const -> void
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

auto __XXECS::Window::Update() const -> void
{
    glfwWaitEvents();

    if (glfwWindowShouldClose(m_window))
        Application::Get()->Close();
}

auto __XXECS::Window::SetFullscreen(const bool fullscreen) -> void
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

auto __XXECS::Window::GetSize() -> std::pair<float, float>
{
    int width, height;

    glfwGetWindowSize(m_window, &width, &height);

    m_width = width;
    m_height = height;

    return {static_cast<float>(width), static_cast<float>(height)};
}

auto __XXECS::Window::GetWidth() -> float
{
    auto [width, height] = GetSize();
    return width;
}

auto __XXECS::Window::GetHeight() -> float
{
    auto [width, height] = GetSize();
    return height;
}

auto __XXECS::Window::GetPos() const -> std::pair<float, float>
{
    int x, y;

    glfwGetWindowPos(m_window, &x, &y);

    return {static_cast<float>(x), static_cast<float>(y)};
}

auto __XXECS::Window::GetPosX() const -> float
{
    auto [x, y] = GetPos();
    return x;
}

auto __XXECS::Window::GetPosY() const -> float
{
    auto [x, y] = GetPos();
    return y;
}
