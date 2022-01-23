#include "pch.h"
#include "Chaos/ECS/Entity.h"

namespace Chaos
{
	Entity Entity::Null = Entity(entt::null, nullptr);

	Entity::Entity(entt::entity id, World* world)
		: m_ID(id), m_World(world)
	{}
}