#include "ECS/Systems/RenderSystems.h"
#include "ECS/Components/BaseComponents.h"
#include "ECS/Components/PhysicsComponents.h"
#include "ECS/Components/RenderComponents.h"

#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>

void UpdateCircleGlowRenderSystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [entityID, positionComp, circleGlowComp] : world.View<PositionComponent, CircleGlowComponent>().each())
	{
		Chaos::Renderer::DrawCircle(positionComp.Position, circleGlowComp.Radius, circleGlowComp.CircleProps);
	}
}

void UpdateCircleRenderSystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [entityID, positionComp, circleComp] : world.View<PositionComponent, CircleComponent>().each())
	{
		Chaos::Renderer::DrawCircle(positionComp.Position, circleComp.Radius, circleComp.CircleProps);
	}
}

void UpdateAimIndicatorRenderSystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [entityID, positionComp, aimComponent, aimIndicatorComponent] : 
		world.View<PositionComponent, AimComponent, AimIndicatorComponent>().each())
	{
		auto position = positionComp.Position + aimComponent.Direction * aimIndicatorComponent.Distance;
		Chaos::Renderer::DrawPolygon(
			position, 
			glm::orientedAngle({ 0.0f, 1.0f }, aimComponent.Direction),
			{ aimIndicatorComponent.Size, aimIndicatorComponent.Size }, 
			aimIndicatorComponent.PolygonProps);
	}
}

void UpdateTrailEffectSystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [entityID, positionComp, trailEffecComp] : world.View<PositionComponent, TrailEffectComponent>().each())
	{
		auto direction = glm::normalize(positionComp.Position - trailEffecComp.LastPosition);
		auto distance = glm::length(positionComp.Position - trailEffecComp.LastPosition);
		auto particlesF = distance * trailEffecComp.TrailEffect.ParticleCountPerUnit + trailEffecComp.Remainder;
		auto particles = static_cast<uint32_t>(floor(particlesF));
		auto deltaPos = direction * (distance / particles);

		for (uint32_t i = 0; i < particles; i++)
		{
			auto particleDirection = direction;

			switch (trailEffecComp.TrailEffect.Direction)
			{
			case VFX::TrailEffect::DirectionType::Forward:
				break;
			case VFX::TrailEffect::DirectionType::Sin:
				particleDirection = Chaos::Math::PerpendicularClockwise(direction) * 
					glm::sin(trailEffecComp.Distance + static_cast<float>(i) * deltaPos);
				break;
			case VFX::TrailEffect::DirectionType::Cos:
				particleDirection = Chaos::Math::PerpendicularClockwise(direction) *
					glm::cos(trailEffecComp.Distance + static_cast<float>(i) * deltaPos);
				break;
			}

			world.GetParticleSystem().EmitFromPoint(
				trailEffecComp.TrailEffect.ParticleProps, 
				trailEffecComp.LastPosition + static_cast<float>(i) * deltaPos, 
				particleDirection,
				1);
		}

		trailEffecComp.Remainder = particlesF - static_cast<float>(particles);
		trailEffecComp.Distance += distance;
		trailEffecComp.LastPosition = positionComp.Position;
	}
}

void UpdateImpactEffectSystem(World& world, Chaos::Timestep ts)
{
	// Update time to next impact effect
	for (auto&& [entityID, impactEffectComp] : world.View<ImpactEffectComponent>().each())
	{
		impactEffectComp.TimeLeft = glm::max(impactEffectComp.TimeLeft - ts.GetDeltaTime(), 0.0f);
	}

	for (auto&& [entityID, collisionComp, impactEffectComp] : world.View<CollisionComponent, ImpactEffectComponent>().each())
	{
		if (impactEffectComp.TimeLeft == 0.0f)
		{
			impactEffectComp.TimeLeft = impactEffectComp.Cooldown;

			world.GetParticleSystem().EmitFromPoint(
				impactEffectComp.ImpactEffect.ParticleProps, 
				collisionComp.Position, 
				-collisionComp.Normal, 
				impactEffectComp.ImpactEffect.ParticleCount);
		}
	}
}

void UpdateParticleEffectRenderSystem(World& world, Chaos::Timestep ts)
{
	world.GetParticleSystem().OnUpdate(ts);
	world.GetParticleSystem().OnRender();
}