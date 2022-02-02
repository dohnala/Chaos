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
		auto direction = glm::normalize(trailEffecComp.LastPosition - positionComp.Position);
		float distance = glm::length(positionComp.Position - trailEffecComp.LastPosition);
		float particlesF = distance * trailEffecComp.ParticleCountPerUnit + trailEffecComp.Remainder;
		uint32_t particles = static_cast<uint32_t>(floor(particlesF));

		world.GetParticleSystem().EmitFromLine(trailEffecComp.ParticleProps, trailEffecComp.LastPosition, positionComp.Position, particles);

		trailEffecComp.Remainder = particlesF - static_cast<float>(particles);
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
				impactEffectComp.ParticleProps, 
				collisionComp.Position, 
				-collisionComp.Normal, 
				impactEffectComp.ParticleCount);
		}
	}
}

void UpdateParticleEffectRenderSystem(World& world, Chaos::Timestep ts)
{
	world.GetParticleSystem().OnUpdate(ts);
	world.GetParticleSystem().OnRender();
}