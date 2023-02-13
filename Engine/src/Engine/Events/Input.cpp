#include "Input.hpp"

#include "Engine/Core/Application.hpp"

auto __XXECS::Input::IsKeyPressed(Key keycode) -> bool
{
	const auto window = Application::Get()->GetWindow().GetNative();
	const auto state = glfwGetKey(window, static_cast<int>(keycode));
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

auto __XXECS::Input::IsMouseButtonPressed(Mouse button) -> bool
{
	const auto window = Application::Get()->GetWindow().GetNative();
	const auto state = glfwGetMouseButton(window, static_cast<int>(button));
	return state == GLFW_PRESS;
}

auto __XXECS::Input::GetMousePosition() -> std::pair<float, float>
{
	const auto window = Application::Get()->GetWindow().GetNative();
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

	return {static_cast<float>(xPos), static_cast<float>(yPos)};
}

auto __XXECS::Input::GetMouseX() -> float
{
	auto [x, y] = GetMousePosition();
	return x;
}

auto __XXECS::Input::GetMouseY() -> float
{
	auto [x, y] = GetMousePosition();
	return y;
}
