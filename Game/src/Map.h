#pragma once

#include "Chaos.h"

#include "Player.h"
#include "CircleShape.h"

struct Collectible : public CircleShape
{
	virtual const glm::vec2& GetPosition() const override { return Position; }
	virtual const float GetRadius() const override { return Radius * InnerRadiusPerc; }
	virtual const float GetDisplayRadius() const override { return Radius; };
	
	// Appearance
	inline static const float Radius = 0.5f;
	inline static const float InnerRadiusPerc = 0.5f;
	inline static const float OuterAlpha = 0.2f;
	inline static glm::vec4 Color = Color::Yellow;

	glm::vec2 Position;
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
private:
	void CreateCollectible(uint32_t index);
	bool CheckCollisiton(const CircleShape& circleA, const CircleShape& circleB);
	glm::vec2 GetRandomLocation(const CircleShape& gameObject);
private:
	glm::vec2 m_MapSize;
	Player m_Player;
	std::vector<Collectible> m_Collectibles;
};