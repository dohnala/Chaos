#include "ECS/Systems/ProjectileSystems.h"
#include "ECS/Components/BaseComponents.h"
#include "ECS/Components/ProjectileComponents.h"
#include "ECS/Components/PhysicsComponents.h"

void UpdateProjectileCollisionSystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [entityID, projectileComp, collisionComp] : world.View<ProjectileComponent, CollisionComponent>().each())
	{
		auto entity = Chaos::Entity(entityID, &world);

		entity.AddComponent<DestroyComponent>(0.0f);
	}
}