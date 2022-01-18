#include "pch.h"
#include "Chaos/ECS/Entity.h"

namespace Chaos
{
	Entity::Entity(entt::entity id, World* world)
		: m_ID(id), m_World(world)
	{}
}