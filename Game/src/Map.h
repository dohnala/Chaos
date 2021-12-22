#pragma once

#include "Chaos.h"

#include "Player.h"
#include "CircleShape.h"

struct Collectible : public CircleShape
{
	virtual const glm::vec2& GetPosition() const override { return Position; }
	virtual const float GetRadius() const override { return Radius * InnerRadiusPerc; }
	
	// Appearance
	inline static const float Radius = 0.5f;
	inline static const float InnerRadiusPerc = 0.5f;
	inline static const float OuterAlpha = 0.2f;
	inline static glm::vec4 Color = Color::Yellow;

	glm::vec2 Position;
};

class Map
{
public:
	void Init();

	void OnUpdate(Chaos::Timestep ts);
	void OnRender();
private:
	bool CheckCollisiton(const CircleShape& circleA, const CircleShape& circleB);
private:
	Player m_Player;
	std::vector<Collectible> m_Collectibles;
};