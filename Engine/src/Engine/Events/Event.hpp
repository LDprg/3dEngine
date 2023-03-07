/*****************************************************************/ /**
 * \file   Event.hpp
 * \brief  Event definitions
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

#include "Key.hpp"

#include <any>
#include <queue>

namespace XXECS::Event
{
    struct ExitEvent
    {
    };

    struct KeyEvent
    {
        Key key;
        Action action;
    };

    struct ResizeEvent
    {
        int width;
        int height;
    };

    struct MouseMovedEvent
    {
        int x;
        int y;
    };

    class EventManager final
    {
    public:
        EventManager() = default;
        ~EventManager() = default;

        auto Push(const std::any &ptr) -> void
        {
            m_apiThreadEvents.push(ptr);
        }

        auto Pop() -> std::any
        {
            std::any val;

            if (!m_apiThreadEvents.empty())
            {
                val = m_apiThreadEvents.front();
                m_apiThreadEvents.pop();
            }

            return val;
        }

    private:
        std::queue<std::any> m_apiThreadEvents;
    };

}
