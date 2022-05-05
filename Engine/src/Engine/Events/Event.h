#pragma once
#include "Key.h"

#include <bx/allocator.h>
#include <bx/spscqueue.h>

namespace __XXECS
{
	enum class EventType
	{
		Exit,
		Key,
		Resize
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

	class EventManager final
	{
	public:
		EventManager()
			: m_apiThreadEvents(&m_allocator)
		{
		}

		virtual ~EventManager()
		{
		}

		void Push(void* ptr) { return m_apiThreadEvents.push(ptr); }

		void* Pop() { return m_apiThreadEvents.pop(); }

		void* Peek() { return m_apiThreadEvents.peek(); }

	private:
		bx::DefaultAllocator m_allocator;
		bx::SpScUnboundedQueue m_apiThreadEvents;
	};
}
