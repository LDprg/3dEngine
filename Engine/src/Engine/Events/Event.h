#pragma once

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
		int key;
		int action;
	};

	struct ResizeEvent
	{
		EventType type = EventType::Resize;
		uint32_t width;
		uint32_t height;
	};

	class EventManager
	{
	public:
		EventManager()
			:m_apiThreadEvents(&m_allocator)
		{}

		virtual ~EventManager() {}

		inline void push(void * _ptr)
		{
			return m_apiThreadEvents.push(std::move(_ptr));
		}

		inline void* pop()
		{
			return m_apiThreadEvents.pop();
		}

		inline void* peek()
		{
			return m_apiThreadEvents.peek();
		}

	private:
		bx::DefaultAllocator m_allocator;
		bx::SpScUnboundedQueue m_apiThreadEvents;
	};
}