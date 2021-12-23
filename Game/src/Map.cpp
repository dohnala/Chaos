#include "Map.h"
#include "Color.h"

void Map::Init(const MapProps& mapProps)
{
	m_MapSize = mapProps.MapSize;

	m_Player.Init({ 0.0f, 0.0f });

	m_Collectibles.resize(mapProps.CollectibleCount);

	for (uint32_t i = 0; i < m_Collectibles.size(); i++)
		CreateCollectible(i);
}

void Map::OnUpdate(Chaos::Timestep ts)
{
	m_Player.OnUpdate(ts);

	for (uint32_t i = 0; i < m_Collectibles.size(); i++)
	{
		if (CheckCollisiton(m_Player, m_Collectibles[i]))
		{
			CreateCollectible(i);
		}
	}
}

void Map::OnRender()
{
	for (const auto& collectible : m_Collectibles)
		Chaos::Renderer::DrawCircle(collectible.GetPosition(), collectible.Radius, collectible.Color, collectible.InnerRadiusPerc, collectible.OuterAlpha);

	m_Player.OnRender();
}

void Map::CreateCollectible(uint32_t index)
{
	Collectible& collectible = m_Collectibles[index];
	collectible.SetPosition(GetRandomLocation(collectible));
}

bool Map::CheckCollisiton(const CircleShape& circleA, const CircleShape& circleB)
{
	auto distance = glm::distance(circleA.GetPosition(), circleB.GetPosition());

	return distance <= circleA.GetRadius() + circleB.GetRadius();
}

glm::vec2 Map::GetRandomLocation(const CircleShape& circle)
{
	float width = m_MapSize.x - 2 * circle.GetDisplayRadius();
	float height = m_MapSize.y - 2 * circle.GetDisplayRadius();
	
	return {
		Chaos::Random::Float() * width - width * 0.5f,
		Chaos::Random::Float() * height - height * 0.5f,
	};
}