/*****************************************************************/ /**
 * \file   Window.hpp
 * \brief  Window class, Window management
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

#include <Engine/Core/Log.hpp>
#include <GLFW/glfw3.h>

namespace __XXECS
{
    class Window final
    {
    public:
        Window() = default;

        ~Window() = default;

        auto Init() -> void;
        auto Close() const -> void;

        auto Update() const -> void;

        auto SetFullscreen(bool fullscreen) -> void;

        auto IsFullscreen() const -> bool
        {
            return m_isFullscreen;
        }

        auto GetNative() const -> GLFWwindow*
        {
            return m_window;
        }

        auto GetSize() -> std::pair<float, float>;
        auto GetWidth() -> float;
        auto GetHeight() -> float;

        auto GetPos() const -> std::pair<float, float>;
        auto GetPosX() const -> float;
        auto GetPosY() const -> float;

    private:
        GLFWwindow *m_window = nullptr;
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
