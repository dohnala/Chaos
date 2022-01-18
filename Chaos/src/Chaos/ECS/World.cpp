#include "pch.h"
#include "Chaos/ECS/World.h"

#include "Chaos/ECS/Entity.h"

namespace Chaos
{
	Entity World::CreateEntity()
	{
		return { m_Registry.create(), this };
	}

	void World::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

	void World::AddSystem(SystemFn systemFn)
	{
		m_Systems.push_back(systemFn);
	}

	void World::OnUpdate(Timestep ts)
	{
		for (auto system : m_Systems)
		{
			system(*this, ts);
		}
	}
}