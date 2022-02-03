#include "ECS/Systems/SkillSystems.h"
#include "ECS/Components/BaseComponents.h"
#include "ECS/Components/SkillComponents.h"
#include "ECS/Components/PhysicsComponents.h"
#include "ECS/Components/ProjectileComponents.h"
#include "ECS/Components/RenderComponents.h"

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
		auto direction = owner.GetComponent<AimComponent>().Direction;
		auto projectilePosition = ownerPosition + direction * (ownerRadius + projectileSkillComp.Radius);

		entity.RemoveComponent<SkillActiveComponent>();
		entity.AddComponent<SkillCooldownComponent>(skillComp.Cooldown);

		auto projectile = world.CreateEntity();
		projectile.AddComponent<PositionComponent>(projectilePosition);
		projectile.AddComponent<ProjectileComponent>(skillComp.Skill, skillComp.Owner);

		auto& moveComp = projectile.AddComponent<MoveComponent>(0.0f, projectileSkillComp.Speed, 0.0f);
		moveComp.Direction = direction;
		moveComp.Velocity = direction * projectileSkillComp.Speed;

		projectile.AddComponent<CircleComponent>(projectileSkillComp.Radius, projectileSkillComp.ProjectileProps);
		projectile.AddComponent<CircleColliderComponent>(projectileSkillComp.Radius, Layer::Projectile, Layer::World | Layer::Enemy);
		projectile.AddComponent<TrailEffectComponent>(projectilePosition, projectileSkillComp.TrailEffect);
		projectile.AddComponent<DestroyEffectComponent>(projectileSkillComp.DestroyEffectCount, projectileSkillComp.DestroyEffect);
	}
}