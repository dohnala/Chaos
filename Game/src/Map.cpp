#include "Map.h"
#include "Color.h"

void Map::Init(const MapProps& mapProps)
{
	m_MapSize = mapProps.MapSize;
	m_Bounds = { -m_MapSize * glm::vec2(0.5f), m_MapSize * glm::vec2(0.5) };

	m_Player.Init({ 0.0f, 0.0f });

	m_Collectibles.resize(mapProps.CollectibleCount);

	for (uint32_t i = 0; i < m_Collectibles.size(); i++)
		CreateCollectible(i);
}

void Map::OnUpdate(Chaos::Timestep ts)
{
	m_Player.OnUpdate(ts);

	CheckMapCollision(m_Player);

	if (m_Player.GetProjectile().IsEnabled())
	{
		auto collisionInfo = CheckMapCollision(m_Player.GetProjectile());

		if (collisionInfo.Collision)
			DestroyProjectile(m_Player.GetProjectile(), collisionInfo.NormalDirection);
	}

	for (uint32_t i = 0; i < m_Collectibles.size(); i++)
	{
		if (CheckCollision(m_Player, m_Collectibles[i]).Collision)
		{
			TakeCollectible(i);
		}

		if (m_Player.GetProjectile().IsEnabled())
		{
			auto collisionInfo = CheckCollision(m_Player.GetProjectile(), m_Collectibles[i]);

			if (collisionInfo.Collision)
			{
				DestroyProjectile(m_Player.GetProjectile(), collisionInfo.NormalDirection);
				TakeCollectible(i);
			}
		}
	}

	EmitProjectileTrail(m_Player.GetProjectile());

	m_ParticleSystem.OnUpdate(ts);
}

void Map::OnRender()
{
	for (const auto& collectible : m_Collectibles)
		collectible.OnRender();

	m_Player.OnRender();

	m_ParticleSystem.OnRender();
}

void Map::CreateCollectible(uint32_t index)
{
	Collectible& collectible = m_Collectibles[index];
	collectible.SetPosition(GetRandomLocation(collectible));
}

void Map::TakeCollectible(uint32_t index)
{
	m_ParticleSystem.Emit(Collectible::CollectParticleProps, m_Collectibles[index].GetPosition(), Collectible::CollectParticleCount);

	CreateCollectible(index);
}

void Map::DestroyProjectile(Projectile& projectile, const glm::vec2& direction)
{
	projectile.ExplosionParticleProps.Direction = direction;
	m_ParticleSystem.Emit(projectile.ExplosionParticleProps, projectile.GetPosition(), projectile.ExplosionParticleCount);

	m_Player.GetProjectile().Destroy();
}

void Map::EmitProjectileTrail(Projectile& projectile)
{
	if (projectile.IsEnabled())
	{
		auto direction = glm::normalize(projectile.GetPosition() - projectile.GetOldPosition());
		float distance = glm::length(projectile.GetPosition() - projectile.GetOldPosition());
		uint32_t pixels = (uint32_t)std::ceil(distance * projectile.TrailParticleCountPerUnit);
		auto delta = projectile.GetDirection() * (distance / pixels);

		projectile.TrailParticleProps.Direction = direction;

		for (uint32_t i = 0; i < pixels; i++)
		{
			m_ParticleSystem.Emit(projectile.TrailParticleProps, projectile.GetOldPosition() + (float)i * delta, 1);
		}
	}
}

CollisionInfo Map::CheckMapCollision(CircleEntity& circle)
{
	CollisionInfo collisionInfo = { false, { 0.0f, 0.0f } };

	if (circle.GetPosition().x + circle.GetRadius() >= m_Bounds.Max.x) collisionInfo = { true, { -1.0f,  0.0f } };
	if (circle.GetPosition().x - circle.GetRadius() <= m_Bounds.Min.x) collisionInfo = { true, {  1.0f,  0.0f } };
	if (circle.GetPosition().y + circle.GetRadius() >= m_Bounds.Max.y) collisionInfo = { true, {  0.0f, -1.0f } };
	if (circle.GetPosition().y - circle.GetRadius() <= m_Bounds.Min.y) collisionInfo = { true, {  0.0f,  1.0f } };

	circle.SetPosition(glm::clamp(circle.GetPosition(), 
		m_Bounds.Min + circle.GetRadius(),
		m_Bounds.Max - circle.GetRadius()));

	return collisionInfo;
}

CollisionInfo Map::CheckCollision(const CircleEntity& circleA, const CircleEntity& circleB)
{
	auto distance = glm::distance(circleA.GetPosition(), circleB.GetPosition());

	if (distance <= circleA.GetRadius() + circleB.GetRadius())
		return { true, (circleB.GetPosition() - circleA.GetPosition()) * -1.0f };

	return { false,  { 0.0f, 0.0f } };
}

glm::vec2 Map::GetRandomLocation(const CircleEntity& circle)
{
	float width = m_MapSize.x - 2 * circle.GetRadius();
	float height = m_MapSize.y - 2 * circle.GetRadius();
	
	return {
		Chaos::Random::Float() * width - width * 0.5f,
		Chaos::Random::Float() * height - height * 0.5f,
	};
}