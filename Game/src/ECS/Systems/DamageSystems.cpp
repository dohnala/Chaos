#include "ECS/Systems/DamageSystems.h"
#include "ECS/Components/BaseComponents.h"
#include "ECS/Components/DamageComponents.h"
#include "ECS/Components/RenderComponents.h"

#include <glm/glm.hpp>

void UpdateDamageImpactEffectSystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [entityID, receivedDamageComp, impactEffectComp] : world.View<ReceivedDamageComponent, ImpactEffectComponent>().each())
	{
		world.GetParticleSystem().EmitFromPoint(
			impactEffectComp.ImpactEffect.ParticleProps,
			receivedDamageComp.Position,
			receivedDamageComp.Direction,
			impactEffectComp.ImpactEffect.ParticleCount);
	}
}

void UpdateHealthSystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [entityID, healthComp, receivedDamageComp] : world.View<HealthComponent, ReceivedDamageComponent>().each())
	{
		auto entity = Chaos::Entity(entityID, &world);

		healthComp.Health -= receivedDamageComp.Damage;

		entity.RemoveComponent<ReceivedDamageComponent>();

		if (healthComp.Health <= 0.0f)
		{
			entity.AddComponent<DestroyComponent>(0.0f);
		}
	}
}