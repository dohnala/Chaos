#include "ECS/Systems/BaseSystems.h"

#include <glm/glm.hpp>

void UpdateFollowSystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [entityID, positionComp, followComp] : world.View<PositionComponent, FollowComponent>().each())
	{
		auto target = followComp.Entity.GetComponent<PositionComponent>().Position;
		positionComp.Position += Chaos::Math::Damp(target - positionComp.Position, followComp.Damp, ts.GetDeltaTime());
	}
}