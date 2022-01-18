#include "ECS/Systems/BaseSystems.h"

#include <glm/glm.hpp>

void UpdateFollowSystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [entityID, positionComp, followComp] : world.View<PositionComponent, FollowComponent>().each())
	{
		positionComp.Position = followComp.Entity.GetComponent<PositionComponent>().Position;
	}
}