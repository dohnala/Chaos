#include "ECS/Systems/RenderSystems.h"

#include <glm/glm.hpp>

void UpdateCircleGlowRenderSystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [entityID, positionComp, circleGlowComp] : world.View<PositionComponent, CircleGlowComponent>().each())
	{
		Chaos::Renderer::DrawCircle(positionComp.Position, circleGlowComp.Radius, circleGlowComp.CircleProps);
	}
}

void UpdateCircleShieldRenderSystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [entityID, positionComp, circleShieldComp] : world.View<PositionComponent, CircleShieldComponent>().each())
	{
		auto entity = Chaos::Entity(entityID, &world);

		if (entity.HasComponent<MoveComponent>())
		{
			circleShieldComp.CircleProps.Direction = entity.GetComponent<MoveComponent>().Direction;
		}

		Chaos::Renderer::DrawCircle(positionComp.Position, circleShieldComp.Radius, circleShieldComp.CircleProps);
	}
}

void UpdateCircleRenderSystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [entityID, positionComp, circleComp] : world.View<PositionComponent, CircleComponent>().each())
	{
		auto entity = Chaos::Entity(entityID, &world);

		if (entity.HasComponent<MoveComponent>())
		{
			circleComp.CircleProps.Direction = entity.GetComponent<MoveComponent>().Direction;
		}

		Chaos::Renderer::DrawCircle(positionComp.Position, circleComp.Radius, circleComp.CircleProps);
	}
}

void UpdateParticleEffectRenderSystem(World& world, Chaos::Timestep ts)
{
	world.GetParticleSystem().OnUpdate(ts);
	world.GetParticleSystem().OnRender();
}