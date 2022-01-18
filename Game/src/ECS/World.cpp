#include "ECS/World.h"

#include "Color.h"
#include "ECS/Components/Components.h"
#include "ECS/Systems/Systems.h"
#include "Factory/Factory.h"

#include <glm/glm.hpp>

World::World(glm::vec2 size)
	: m_Size(size), m_Bounds({ -size * glm::vec2(0.5f), size * glm::vec2(0.5) })
{
	m_Player = Factory::CreatePlayer(*this);
	m_Camera = Factory::CreateCamera(*this, m_Player);

	for (uint32_t i = 0; i < 20; i++)
		Factory::CreateCollectible(*this);
}

glm::vec2 World::GetRandomLocation() const
{
	return {
		Chaos::Random::Float() * m_Size.x - m_Size.x * 0.5f,
		Chaos::Random::Float() * m_Size.y - m_Size.y * 0.5f,
	};
}

void World::OnUpdate(Chaos::Timestep ts)
{
	// Input
	UpdateInputMovementSystem(*this, ts);

	// Movement
	UpdateMovementSystem(*this, ts);
	UpdateFollowSystem(*this, ts);

	// Collision
	UpdateCollisionSystem(*this, ts);
	UpdateCameraCollisionSystem(*this, ts);

	// Collectible
	UpdateCollectibleCollisionSystem(*this, ts);

	if (m_Camera)
	{
		Chaos::Renderer::SetClearColor(Color::DarkGrey);
		Chaos::Renderer::Clear();

		Chaos::Renderer::BeginScene(
			m_Camera.GetComponent<CameraComponent>().Camera,
			m_Camera.GetComponent<PositionComponent>().Position,
			ts);

		// Rendering
		UpdateCircleGlowRenderSystem(*this, ts);
		UpdateCircleShieldRenderSystem(*this, ts);
		UpdateCircleRenderSystem(*this, ts);
		UpdateParticleEffectRenderSystem(*this, ts);

		Chaos::Renderer::EndScene();
	}
}

void World::OnViewportResize(uint32_t width, uint32_t height)
{
	if (m_Camera)
	{
		m_Camera.GetComponent<CameraComponent>().Camera.SetViewport(width, height);
	}
}