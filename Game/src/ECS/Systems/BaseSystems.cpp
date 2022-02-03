#include "ECS/Systems/BaseSystems.h"
#include "ECS/Components/BaseComponents.h"
#include "ECS/Components/PhysicsComponents.h"
#include "ECS/Components/RenderComponents.h"

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

void UpdateDestroySystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [entityID, destroyComp] : world.View<DestroyComponent>().each())
	{
		auto entity = Chaos::Entity(entityID, &world);

		destroyComp.Delay -= ts.GetDeltaTime();

		if (destroyComp.Delay <= 0.0f)
		{
			if (entity.HasComponent<DestroyEffectComponent>())
			{
				auto& destroyEffectComp = entity.GetComponent<DestroyEffectComponent>();

				if (entity.HasComponent<CollisionComponent>())
				{
					auto& collision = entity.GetComponent<CollisionComponent>();
					
					world.GetParticleSystem().EmitFromPoint(
						destroyEffectComp.DestroyEffect.ParticleProps,
						collision.Position, 
						collision.Normal, 
						destroyEffectComp.DestroyEffect.ParticleCount);
				}
				else if (entity.HasComponent<PositionComponent>())
				{
					auto& positionComp = entity.GetComponent<PositionComponent>();
					
					world.GetParticleSystem().EmitFromPoint(
						destroyEffectComp.DestroyEffect.ParticleProps, 
						positionComp.Position,
						destroyEffectComp.DestroyEffect.ParticleCount);
				}
			}

			world.DestroyEntity(entity);
		}
	}
}