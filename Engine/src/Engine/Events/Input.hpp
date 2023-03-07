/*****************************************************************/ /**
 * \file   Input.hpp
 * \brief  Input management
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once
#include <Engine/Events/Key.hpp>

namespace XXECS
{
    class Input
    {
    public:
        static auto IsKeyPressed(Key keycode) -> bool;
        static auto IsMouseButtonPressed(Mouse button) -> bool;

        static auto GetMousePosition() -> std::pair<float, float>;
        static auto GetMouseX() -> float;
        static auto GetMouseY() -> float;
    };
}
