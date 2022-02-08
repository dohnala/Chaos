#include "ECS/Systems/RenderSystems.h"
#include "ECS/Components/BaseComponents.h"
#include "ECS/Components/PhysicsComponents.h"
#include "ECS/Components/DamageComponents.h"
#include "ECS/Components/RenderComponents.h"

#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>

static Chaos::CircleProps s_HealthBarBackground = Chaos::CircleProps::Create()
	.WithColor(Color::DarkGrey);

static Chaos::CircleProps s_HealthBarInactive = Chaos::CircleProps::Create()
	.WithGaps(10, 0.0f)
	.WithColor(Color::Grey);

static Chaos::CircleProps s_HealthBarActive = Chaos::CircleProps::Create()
	.WithGaps(10, 0.0f);

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

void UpdateHealthBarRenderSystem(World& world, Chaos::Timestep ts)
{

	for (auto&& [entityID, positionComp, healthComp, healthBarComp] : world.View<PositionComponent, HealthComponent, HealthBarComponent>().each())
	{
		s_HealthBarBackground.WithThickness(healthBarComp.BackgroundThickness);
		s_HealthBarInactive.WithThickness(healthBarComp.Thickness);
		s_HealthBarActive
			.WithThickness(healthBarComp.Thickness)
			.WithCircumference(healthComp.MaxHealth <= 0.0f ? 0.0f : healthComp.Health / healthComp.MaxHealth)
			.WithColor(healthBarComp.Color);

		Chaos::Renderer::DrawCircle(positionComp.Position, healthBarComp.Radius + healthBarComp.Thickness * 0.5f, s_HealthBarBackground);
		Chaos::Renderer::DrawCircle(positionComp.Position, healthBarComp.Radius, s_HealthBarInactive);
		Chaos::Renderer::DrawCircle(positionComp.Position, healthBarComp.Radius, s_HealthBarActive);
	}
}

void UpdateTrailEffectRenderSystem(World& world, Chaos::Timestep ts)
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

			world.GetTrailParticleSystem().EmitFromPoint(
				trailEffecComp.TrailEffect.ParticleProps, 
				trailEffecComp.LastPosition + static_cast<float>(i) * deltaPos, 
				particleDirection,
				1);
		}

		trailEffecComp.Remainder = particlesF - static_cast<float>(particles);
		trailEffecComp.Distance += distance;
		trailEffecComp.LastPosition = positionComp.Position;
	}

	world.GetTrailParticleSystem().OnUpdate(ts);
	world.GetTrailParticleSystem().OnRender();
}

void UpdateParticleEffectRenderSystem(World& world, Chaos::Timestep ts)
{
	world.GetParticleSystem().OnUpdate(ts);
	world.GetParticleSystem().OnRender();
}