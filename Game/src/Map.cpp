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

	for (uint32_t i = 0; i < m_Collectibles.size(); i++)
	{
		if (CheckCollision(m_Player, m_Collectibles[i]))
		{
			CreateCollectible(i);
		}
	}
}

void Map::OnRender()
{
	for (const auto& collectible : m_Collectibles)
		collectible.OnRender();

	m_Player.OnRender();
}

void Map::CreateCollectible(uint32_t index)
{
	Collectible& collectible = m_Collectibles[index];
	collectible.SetPosition(GetRandomLocation(collectible));
}

void Map::CheckMapCollision(CircleEntity& circle)
{
	circle.SetPosition(glm::clamp(circle.GetPosition(), 
		m_Bounds.Min + circle.GetColliderRadius(),
		m_Bounds.Max - circle.GetColliderRadius()));
}

bool Map::CheckCollision(const CircleEntity& circleA, const CircleEntity& circleB)
{
	auto distance = glm::distance(circleA.GetPosition(), circleB.GetPosition());

	return distance <= circleA.GetColliderRadius() + circleB.GetColliderRadius();
}

glm::vec2 Map::GetRandomLocation(const CircleEntity& circle)
{
	float width = m_MapSize.x - 2 * circle.GetRenderRadius();
	float height = m_MapSize.y - 2 * circle.GetRenderRadius();
	
	return {
		Chaos::Random::Float() * width - width * 0.5f,
		Chaos::Random::Float() * height - height * 0.5f,
	};
}