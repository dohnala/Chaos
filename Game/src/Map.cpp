#include "Map.h"
#include "Color.h"

void Map::Init()
{
	m_Player.Init({ 0.0f, 0.0f });

	m_Collectibles.resize(4);
	m_Collectibles[0].Position = { -4.0f, -4.0f };
	m_Collectibles[1].Position = {  4.0f, -4.0f };
	m_Collectibles[2].Position = {  4.0f,  4.0f };
	m_Collectibles[3].Position = { -4.0f,  4.0f };
}

void Map::OnUpdate(Chaos::Timestep ts)
{
	m_Player.OnUpdate(ts);

	for (const auto& collectible : m_Collectibles)
	{
		if (CheckCollisiton(m_Player, collectible))
		{
			CH_TRACE("Collision");
		}
	}
}

void Map::OnRender()
{
	for (const auto& collectible : m_Collectibles)
	{
		Chaos::Renderer::DrawCircle(collectible.Position, collectible.Radius, collectible.Color, collectible.InnerRadiusPerc, collectible.OuterAlpha);
	}

	m_Player.OnRender();
}

bool Map::CheckCollisiton(const CircleShape& circleA, const CircleShape& circleB)
{
	auto distance = glm::distance(circleA.GetPosition(), circleB.GetPosition());

	return distance <= circleA.GetRadius() + circleB.GetRadius();
}