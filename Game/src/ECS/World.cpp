#include "ECS/World.h"

#include "Color.h"
#include "ECS/Components/Components.h"
#include "ECS/Systems/Systems.h"
#include "Factory/Factory.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

World::World(glm::vec2 size)
	: m_Size(size), m_Bounds({ -size * glm::vec2(0.5f), size * glm::vec2(0.5) })
{
	m_Player = Factory::CreatePlayer(*this);
	m_Camera = Factory::CreateCamera(*this, m_Player);

	for (uint32_t i = 0; i < 20; i++)
		Factory::CreateCollectible(*this);
}

void World::OnUpdate(Chaos::Timestep ts)
{
	// Input
	UpdateInputMovementSystem(*this, ts);
	UpdateInputSkillSystem(*this, ts);

	// Skills
	UpdateSkillCooldownSystem(*this, ts);
	UpdateProjectileSkillSystem(*this, ts);

	// Movement
	UpdateMovementSystem(*this, ts);
	UpdateFollowSystem(*this, ts);

	// Collision
	UpdateCollisionSystem(*this, ts);
	UpdateCameraCollisionSystem(*this, ts);

	// Collectible
	UpdateCollectibleCollisionSystem(*this, ts);

	// Projectile
	UpdateProjectileDestroySystem(*this, ts);

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
		UpdateCreatureRenderSystem(*this, ts);
		UpdateCircleRenderSystem(*this, ts);
		UpdateTrailEffectSystem(*this, ts);
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
glm::vec2 World::GetRandomLocation() const
{
	return {
		Chaos::Random::Float() * m_Size.x - m_Size.x * 0.5f,
		Chaos::Random::Float() * m_Size.y - m_Size.y * 0.5f,
	};
}

glm::vec2 World::ScreenToWorldPosition(const glm::vec2& screenPosition) const
{
	auto &camera = m_Camera.GetComponent<CameraComponent>().Camera;
	auto &cameraPosition = m_Camera.GetComponent<PositionComponent>().Position;

	auto viewMatrix = glm::inverse(glm::translate(glm::mat4(1.0f), { cameraPosition.x, cameraPosition.y, 0.0f }));

	auto worldPosition = glm::unProject(
		glm::vec3(screenPosition.x, camera.GetViewport().w - screenPosition.y, 0.0f), 
		viewMatrix,
		camera.GetProjection(),
		camera.GetViewport());

	return { worldPosition.x, worldPosition.y };
}
