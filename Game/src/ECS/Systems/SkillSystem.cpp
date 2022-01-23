#include "ECS/Systems/SkillSystems.h"

void UpdateSkillCooldownSystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [entityID, skillCooldownComp] : world.View<SkillCooldownComponent>().each())
	{
		auto entity = Chaos::Entity(entityID, &world);

		skillCooldownComp.TimeLeft -= ts.GetDeltaTime();

		if (skillCooldownComp.TimeLeft <= 0.0f)
		{
			entity.RemoveComponent<SkillCooldownComponent>();
		}
	}
}

void UpdateProjectileSkillSystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [entityID, skillComp, skillActiveComp, projectileSkillComp] :
		world.View<SkillComponent, SkillActiveComponent, ProjectileSkillComponent>().each())
	{
		auto entity = Chaos::Entity(entityID, &world);
		auto owner = skillComp.Owner;
		auto ownerPosition = owner.GetComponent<PositionComponent>().Position;
		auto ownerRadius = owner.GetComponent<CircleColliderComponent>().Radius;
		auto targetPosition = world.ScreenToWorldPosition(Chaos::Input::GetMousePosition());
		auto direction = glm::normalize(targetPosition - ownerPosition);
		auto projectilePosition = ownerPosition + direction * (ownerRadius + projectileSkillComp.Radius);

		entity.RemoveComponent<SkillActiveComponent>();
		entity.AddComponent<SkillCooldownComponent>(skillComp.Cooldown);

		auto projectile = world.CreateEntity();
		projectile.AddComponent<PositionComponent>(projectilePosition);
		projectile.AddComponent<ProjectileComponent>(skillComp.Skill, skillComp.Owner);
		projectile.AddComponent<MoveComponent>(projectileSkillComp.Speed, direction);
		projectile.AddComponent<CircleComponent>(projectileSkillComp.Radius, projectileSkillComp.ProjectileProps);
		projectile.AddComponent<CircleColliderComponent>(projectileSkillComp.Radius);
		projectile.AddComponent<TrailEffectComponent>(projectilePosition, projectileSkillComp.TrailEffectCountPerUnit, projectileSkillComp.TrailEffect);
		projectile.AddComponent<DestroyEffectComponent>(projectileSkillComp.DestroyEffectCount, projectileSkillComp.DestroyEffect);
	}
}

void UpdateProjectileDestroySystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [entityID, projectileComp, collisionComp] : world.View<ProjectileComponent, CollisionComponent>().each())
	{
		auto entity = Chaos::Entity(entityID, &world);

		if (entity.HasComponent<DestroyEffectComponent>())
		{
			auto& effect = entity.GetComponent<DestroyEffectComponent>();
			world.GetParticleSystem().EmitFromPoint(effect.ParticleProps, collisionComp.Position, collisionComp.Normal, effect.ParticleCount);
		}

		world.DestroyEntity(entity);
	}
}