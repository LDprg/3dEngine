#pragma once
#include <entt/entt.hpp>

namespace __XXECS
{
	class EntityManager
	{
	public:
		EntityManager() = default;
		~EntityManager() = default;

		entt::registry& GetNative()
		{
			return m_registry;
		}

	private:
		entt::registry m_registry;
	};
}