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

	const Chaos::Bounds& GetBounds() const { return m_Bounds; }
	const Player& GetPlayer() const { return m_Player; }
private:
	void CreateCollectible(uint32_t index);
	void TakeCollectible(uint32_t index);
	
	bool CheckMapCollision(CircleEntity& circle);
	bool CheckCollision(const CircleEntity& circleA, const CircleEntity& circleB);
	
	glm::vec2 GetRandomLocation(const CircleEntity& circle);
private:
	glm::vec2 m_MapSize;
	Chaos::Bounds m_Bounds;

	Player m_Player;
	std::vector<Collectible> m_Collectibles;

	Chaos::ParticleProps m_CollectParticle;
	Chaos::ParticleSystem m_CollectParticleSystem = Chaos::ParticleSystem(100);
};