#include "ECS/Systems/CollectibleSystems.h"

#include <glm/glm.hpp>

void UpdateCollectibleCollisionSystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [entityID, collectibleComp, collisionComp] : world.View<CollectibleComponent, CollisionComponent>().each())
	{
		auto entity = Chaos::Entity(entityID, &world);

		if (entity.HasComponent<DestroyEffectComponent>())
		{
			auto& effect = entity.GetComponent<DestroyEffectComponent>();
			world.GetParticleSystem().EmitFromPoint(effect.ParticleProps, collisionComp.Position, effect.ParticleCount);
		}

		world.DestroyEntity(entity);
	}
}