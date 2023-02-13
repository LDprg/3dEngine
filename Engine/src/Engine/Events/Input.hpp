#pragma once
#include <Engine/Events/Key.hpp>

namespace __XXECS
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
