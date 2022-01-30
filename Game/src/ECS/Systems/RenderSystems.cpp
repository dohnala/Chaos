#include "ECS/Systems/RenderSystems.h"

#include <glm/glm.hpp>

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
		auto entity = Chaos::Entity(entityID, &world);

		Chaos::Renderer::DrawCircle(positionComp.Position, circleComp.Radius, circleComp.CircleProps);
	}
}

void UpdateCreatureRenderSystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [entityID, positionComp, creatureComp] : world.View<PositionComponent, CreatureComponent>().each())
	{
		auto entity = Chaos::Entity(entityID, &world);

		if (entity.HasComponent<MoveComponent>())
		{
			auto& moveComp = entity.GetComponent<MoveComponent>();
			creatureComp.CreatureProps.Velocity = moveComp.Velocity;
		}

		Chaos::Renderer::DrawCreature(positionComp.Position, creatureComp.Radius, creatureComp.CreatureProps);
	}
}

void UpdateTrailEffectSystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [entityID, positionComp, trailEffecComp] : world.View<PositionComponent, TrailEffectComponent>().each())
	{
		auto direction = glm::normalize(trailEffecComp.LastPosition - positionComp.Position);
		float distance = glm::length(positionComp.Position - trailEffecComp.LastPosition);
		uint32_t particles = (uint32_t)std::ceil(distance * trailEffecComp.ParticleCountPerUnit);

		world.GetParticleSystem().EmitFromLine(trailEffecComp.ParticleProps, trailEffecComp.LastPosition, positionComp.Position, particles);

		trailEffecComp.LastPosition = positionComp.Position;
	}
}

void UpdateParticleEffectRenderSystem(World& world, Chaos::Timestep ts)
{
	world.GetParticleSystem().OnUpdate(ts);
	world.GetParticleSystem().OnRender();
}