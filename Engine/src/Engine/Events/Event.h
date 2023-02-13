#pragma once
#include <queue>
#include <any>

#include "Key.h"

namespace __XXECS
{
	enum class EventType
	{
		Exit,
		Key,
		Resize,
		MouseMoved
	};

	struct ExitEvent
	{
		EventType type = EventType::Exit;
	};

	struct KeyEvent
	{
		EventType type = EventType::Key;
		Key key;
		Action action;
	};

	struct ResizeEvent
	{
		EventType type = EventType::Resize;
		int width;
		int height;
	};

	struct MouseMovedEvent
	{
		EventType type = EventType::MouseMoved;
		int x;
		int y;
	};

	class EventManager final
	{
	public:
		EventManager()
		{
		}

		~EventManager()
		{
		}

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

			return std::move(val);
		}

	private:
		std::queue<std::any> m_apiThreadEvents;
	};
}
