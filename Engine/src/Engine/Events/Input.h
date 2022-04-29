#pragma once
#include <utility>

#include "Key.h"

namespace __XXECS
{
	class Input
	{
	public:
		static bool IsKeyPressed(Key keycode);
		static bool IsMouseButtonPressed(Mouse button);

		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}
