#include "ECS/Systems/BaseSystems.h"
#include "ECS/Components/BaseComponents.h"

#include <glm/glm.hpp>

void UpdateFollowSystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [entityID, positionComp, followComp] : world.View<PositionComponent, FollowComponent>().each())
	{
		auto target = followComp.Entity.GetComponent<PositionComponent>().Position;
		auto distance = glm::length(target - positionComp.Position);
		
		auto damp = followComp.Distance == 0.0f ? followComp.DampMin : 
			glm::mix(followComp.DampMin, followComp.DampMax, glm::min(distance / followComp.Distance, 1.0f));
		
		positionComp.Position += Chaos::Math::Damp(target - positionComp.Position, damp, ts.GetDeltaTime());
	}
}