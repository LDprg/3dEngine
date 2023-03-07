/*****************************************************************/ /**
 * \file   Input.cpp
 * \brief  Input source
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#include "Input.hpp"

#include "Engine/Core/Application.hpp"

using namespace XXECS;

auto Input::IsKeyPressed(Key keycode) -> bool
{
    const auto window = Application::Get()->GetWindow().GetNative();
    const auto state = glfwGetKey(window, static_cast<int>(keycode));
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

auto Input::IsMouseButtonPressed(Mouse button) -> bool
{
    const auto window = Application::Get()->GetWindow().GetNative();
    const auto state = glfwGetMouseButton(window, static_cast<int>(button));
    return state == GLFW_PRESS;
}

auto Input::GetMousePosition() -> std::pair<float, float>
{
    const auto window = Application::Get()->GetWindow().GetNative();
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);

    return {static_cast<float>(xPos), static_cast<float>(yPos)};
}

auto Input::GetMouseX() -> float
{
    auto [x, y] = GetMousePosition();
    return x;
}

auto Input::GetMouseY() -> float
{
    auto [x, y] = GetMousePosition();
    return y;
}
