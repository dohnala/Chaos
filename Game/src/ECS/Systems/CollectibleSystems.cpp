#include "ECS/Systems/CollectibleSystems.h"

#include <glm/glm.hpp>

void UpdateCollectibleFollowSystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [entityID, positionComp, collectibleFollowComp] : world.View<PositionComponent, CollectibleFollowComponent>().each())
	{
		auto entity = Chaos::Entity(entityID, &world);

		for (auto&& [collectibleEntityID, collectiblePositionComp, collectibleComp] : 
			world.View<PositionComponent, CollectibleComponent>(entt::exclude<FollowComponent>).each())
		{
			auto collectibleEntity = Chaos::Entity(collectibleEntityID, &world);

			auto distance = glm::length(collectiblePositionComp.Position - positionComp.Position);

			if (distance <= collectibleFollowComp.Radius)
			{
				collectibleEntity.AddComponent<FollowComponent>(entity, 
					collectibleFollowComp.DampMin,
					collectibleFollowComp.DampMax,
					collectibleFollowComp.Radius);
			}
		}
	}
}

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