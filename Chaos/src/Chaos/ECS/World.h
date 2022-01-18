#pragma once

#include "Chaos/Core/Base.h"
#include "Chaos/Core/Timestep.h"

#include <entt/entity/registry.hpp>

namespace Chaos
{
	class Entity;

	class World
	{
	public:
		using SystemFn = std::function<void(World&, Timestep)>;

		World() = default;
		~World() = default;

		Entity CreateEntity();
		void DestroyEntity(Entity entity);

		void AddSystem(SystemFn systemFn);

		void OnUpdate(Timestep ts);
	private:
		entt::registry m_Registry;
		std::vector<SystemFn> m_Systems;

		friend class Entity;
	};
}