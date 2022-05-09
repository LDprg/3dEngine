#pragma once
#include <queue>

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

		void Push(void* ptr)
		{
			return m_apiThreadEvents.push(ptr);
		}

		void* Pop()
		{
			if (m_apiThreadEvents.empty())
				return nullptr;

			void* ptr = m_apiThreadEvents.front();
			m_apiThreadEvents.pop();
			return ptr;
		}

	private:
		std::queue<void *> m_apiThreadEvents;
	};
}
