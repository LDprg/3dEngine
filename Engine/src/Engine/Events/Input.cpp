#include "pch.hpp"
#include "Input.h"

#include "Engine/Core/Application.h"

bool __XXECS::Input::IsKeyPressed(Key keycode)
{
	auto window = Application::Get().GetWindow().GetNativeWindow();
	auto state = glfwGetKey(window, (int)keycode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool __XXECS::Input::IsMouseButtonPressed(Mouse button)
{
	auto window = Application::Get().GetWindow().GetNativeWindow();
	auto state = glfwGetMouseButton(window, (int)button);
	return state == GLFW_PRESS;
}

std::pair<float, float> __XXECS::Input::GetMousePosition()
{
	auto window = Application::Get().GetWindow().GetNativeWindow();
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	return { (float)xpos, (float)ypos };
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