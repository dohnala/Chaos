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

	m_CollectParticle.DirectionAngleVariance = glm::radians(360.0f);
	m_CollectParticle.Speed = 3.0f;
	m_CollectParticle.SpeedVariance = 6.0f;
	m_CollectParticle.Size = 0.1f;
	m_CollectParticle.SizeVariance = 0.05f;
	m_CollectParticle.Color = Color::Yellow;
	m_CollectParticle.Alpha = 0.5f;
	m_CollectParticle.AlphaVariance = 1.0f;
	m_CollectParticle.AlphaEnd = 0.0f;
	m_CollectParticle.LifeTime = 1.0f;
	m_CollectParticle.LifeTimeVariance = 1.0f;
}

void Map::OnUpdate(Chaos::Timestep ts)
{
	m_Player.OnUpdate(ts);

	CheckMapCollision(m_Player);

	if (CheckMapCollision(m_Player.GetProjectile()))
	{
		m_Player.GetProjectile().Destroy();
	}

	for (uint32_t i = 0; i < m_Collectibles.size(); i++)
	{
		if (CheckCollision(m_Player, m_Collectibles[i]))
		{
			TakeCollectible(i);
		}

		if (CheckCollision(m_Player.GetProjectile(), m_Collectibles[i]))
		{
			TakeCollectible(i);
			m_Player.GetProjectile().Destroy();
		}
	}

	m_CollectParticleSystem.OnUpdate(ts);
}

void Map::OnRender()
{
	for (const auto& collectible : m_Collectibles)
		collectible.OnRender();

	m_Player.OnRender();

	m_CollectParticleSystem.OnRender();
}

void Map::CreateCollectible(uint32_t index)
{
	Collectible& collectible = m_Collectibles[index];
	collectible.SetPosition(GetRandomLocation(collectible));
}

void Map::TakeCollectible(uint32_t index)
{
	m_CollectParticle.Position = m_Collectibles[index].GetPosition();
	m_CollectParticleSystem.Emit(m_CollectParticle, 10);

	CreateCollectible(index);
}

bool Map::CheckMapCollision(CircleEntity& circle)
{
	bool collision = false;

	if (circle.GetPosition().x + circle.GetRadius() >= m_Bounds.Max.x) collision = true;
	if (circle.GetPosition().x - circle.GetRadius() <= m_Bounds.Min.x) collision = true;
	if (circle.GetPosition().y + circle.GetRadius() >= m_Bounds.Max.y) collision = true;
	if (circle.GetPosition().y - circle.GetRadius() <= m_Bounds.Min.y) collision = true;

	circle.SetPosition(glm::clamp(circle.GetPosition(), 
		m_Bounds.Min + circle.GetRadius(),
		m_Bounds.Max - circle.GetRadius()));

	return collision;
}

bool Map::CheckCollision(const CircleEntity& circleA, const CircleEntity& circleB)
{
	auto distance = glm::distance(circleA.GetPosition(), circleB.GetPosition());

	return distance <= circleA.GetRadius() + circleB.GetRadius();
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