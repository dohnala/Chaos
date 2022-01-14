#pragma once

#include "Chaos.h"

#include "Entities/Player.h"
#include "Entities/Collectible.h"

struct CollisionInfo
{
	bool Collision;
	glm::vec2 NormalDirection;
};

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

	void DestroyProjectile(Projectile& projectile, const glm::vec2& direction);
	void EmitProjectileTrail(Projectile& projectile);
	
	CollisionInfo CheckMapCollision(CircleEntity& circle);
	CollisionInfo CheckCollision(const CircleEntity& circleA, const CircleEntity& circleB);
	
	glm::vec2 GetRandomLocation(const CircleEntity& circle);
private:
	glm::vec2 m_MapSize;
	Chaos::Bounds m_Bounds;

	Player m_Player;
	std::vector<Collectible> m_Collectibles;

	Chaos::ParticleSystem m_ParticleSystem = Chaos::ParticleSystem(500);
};