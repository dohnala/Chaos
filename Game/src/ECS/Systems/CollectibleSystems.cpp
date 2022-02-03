#include "ECS/Systems/CollectibleSystems.h"
#include "ECS/Components/BaseComponents.h"
#include "ECS/Components/CollectibleComponents.h"
#include "ECS/Components/PhysicsComponents.h"
#include "ECS/Components/RenderComponents.h"

#include <limits>
#include <glm/glm.hpp>

void UpdateCollectibleFollowSystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [collectibleID, collectiblePositionComp, collectibleComp] : 
		world.View<PositionComponent, CollectibleComponent>(entt::exclude<FollowComponent>).each())
	{
		auto collectibleEntity = Chaos::Entity(collectibleID, &world);

		float minDistance = std::numeric_limits<float>::max();
		Chaos::Entity closestEntity;
		CollectiblePickupRadiusComponent closestPickupRadiusComponent;

		for (auto&& [entityID, positionComp, pickupRadiusComp] : world.View<PositionComponent, CollectiblePickupRadiusComponent>().each())
		{
			auto entity = Chaos::Entity(entityID, &world);

			auto distance = glm::length(collectiblePositionComp.Position - positionComp.Position);

			if (distance <= pickupRadiusComp.Radius && distance < minDistance)
			{
				minDistance = distance;
				closestEntity = entity;
				closestPickupRadiusComponent = pickupRadiusComp;
			}
		}

		if (closestEntity)
		{
			collectibleEntity.AddComponent<FollowComponent>(closestEntity,
				closestPickupRadiusComponent.DampMin,
				closestPickupRadiusComponent.DampMax,
				closestPickupRadiusComponent.Radius);
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