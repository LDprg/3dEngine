#include "Input.h"

#include "Engine/Core/Application.h"

bool __XXECS::Input::IsKeyPressed(Key keycode)
{
	const auto window = Application::Get().GetWindow().GetNativeWindow();
	const auto state = glfwGetKey(window, static_cast<int>(keycode));
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool __XXECS::Input::IsMouseButtonPressed(Mouse button)
{
	const auto window = Application::Get().GetWindow().GetNativeWindow();
	const auto state = glfwGetMouseButton(window, static_cast<int>(button));
	return state == GLFW_PRESS;
}

std::pair<float, float> __XXECS::Input::GetMousePosition()
{
	const auto window = Application::Get().GetWindow().GetNativeWindow();
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

	return {static_cast<float>(xPos), static_cast<float>(yPos)};
}

float __XXECS::Input::GetMouseX()
{
	auto [x, y] = GetMousePosition();
	return x;
}

float __XXECS::Input::GetMouseY()
{
	auto [x, y] = GetMousePosition();
	return y;
}
