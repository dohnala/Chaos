#include "ECS/Systems/ProjectileSystems.h"
#include "ECS/Components/BaseComponents.h"
#include "ECS/Components/ProjectileComponents.h"
#include "ECS/Components/DamageComponents.h"
#include "ECS/Components/PhysicsComponents.h"

#include <limits>
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>

void UpdateHomingProjectileSystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [projectileID, projectilePositionComp, projectileComp, homingComp, moveComp] :
		world.View<PositionComponent, ProjectileComponent, HomingProjectileComponent, MoveComponent>().each())
	{
		if (homingComp.TargetMask == Layer::None) continue;

		auto projectileEntity = Chaos::Entity(projectileID, &world);

		float minDistance = std::numeric_limits<float>::max();
		Chaos::Entity closestTarget;
		glm::vec2 targetDirection = moveComp.Direction;

		for (auto&& [targetID, targetPositionComp, targetColliderComp] : 
			world.View<PositionComponent, CircleColliderComponent>().each())
		{
			auto targetEntity = Chaos::Entity(targetID, &world);

			if (projectileEntity == targetEntity) continue;
			if (targetColliderComp.BelongsTo == Layer::None) continue;
			if ((homingComp.TargetMask & targetColliderComp.BelongsTo) != targetColliderComp.BelongsTo) continue;

			auto distance = glm::length(targetPositionComp.Position - projectilePositionComp.Position);

			if (distance <= homingComp.Distance && distance < minDistance)
			{
				auto direction = glm::normalize(targetPositionComp.Position - projectilePositionComp.Position);
				auto angle = glm::abs(glm::degrees(glm::orientedAngle(moveComp.Direction, direction)));

				if (angle <= homingComp.Angle)
				{
					minDistance = distance;
					closestTarget = targetEntity;
					targetDirection = direction;
				}
			}
		}

		if (closestTarget)
		{
			moveComp.Direction = targetDirection;
		}
	}
}

void UpdateProjectileCollisionSystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [projectileID, projectileComp, projectileCollisionComp, projectileDamageComp] : 
		world.View<ProjectileComponent, CollisionComponent, DamageComponent>().each())
	{
		auto projectile = Chaos::Entity(projectileID, &world);

		auto target = projectileCollisionComp.Entity;

		if (target && target.HasComponent<DamageableComponent>())
		{
			target.AddComponent<ReceivedDamageComponent>(target, 
				projectileCollisionComp.Position, 
				projectileCollisionComp.Normal, 
				projectileDamageComp.Damage);
		}

		projectile.AddComponent<DestroyComponent>(0.0f);
	}
}