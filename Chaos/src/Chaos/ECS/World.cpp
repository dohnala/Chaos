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
}