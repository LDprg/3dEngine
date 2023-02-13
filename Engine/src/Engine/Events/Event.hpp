#pragma once
#include <any>
#include <queue>

#include "Key.hpp"

namespace __XXECS
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

		void Push(const std::any& ptr)
		{
			m_apiThreadEvents.push(ptr);
		}

		std::any Pop()
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
