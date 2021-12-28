#pragma once

#include "Chaos.h"

#include "Entities/Player.h"
#include "Entities/Collectible.h"

struct MapProps
{
	glm::vec2 MapSize;
	uint32_t CollectibleCount;
};

class Map
{
public:
	void Init(const MapProps& mapProps);

	void OnUpdate(Chaos::Timestep ts);
	void OnRender();

	const Chaos::Bounds GetBounds() const { return { -m_MapSize * glm::vec2(0.5f), m_MapSize * glm::vec2(0.5) }; }
	const Player& GetPlayer() const { return m_Player; }
private:
	void CreateCollectible(uint32_t index);
	bool CheckCollisiton(const CircleEntity& circleA, const CircleEntity& circleB);
	glm::vec2 GetRandomLocation(const CircleEntity& circle);
private:
	glm::vec2 m_MapSize;
	Player m_Player;
	std::vector<Collectible> m_Collectibles;
};