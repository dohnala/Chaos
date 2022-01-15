#pragma once

#include "Chaos.h"
#include "Color.h"
#include "Entities/CircleEntity.h"

class Collectible : public CircleEntity
{
public:
	virtual void OnRender() const override;

	virtual const float GetRadius() const override { return s_Radius; }
public:
	inline static const Chaos::ParticleProps CollectParticleProps = {
		0.0f,											// PositionRadiusVariance
		{ 0.0f, 1.0f }, glm::radians(360.0f),			// Direction, DirectionAngleVariance
		3.0f, 6.0f,										// Speed, SpeedVariance
		0.1f, 0.05f,									// Size, SizeVariance
		Color::Yellow, Color::Yellow,					// ColorFrom, ColorTo
		0.5f, 1.0f, 0.0f,								// Alpha, AlphaVariance, AlphaEnd
		1.0f, 1.0f										// LifeTime, LifeTime
	};

	inline static uint32_t CollectParticleCount = 10;
private:
	inline static const float s_Radius = 0.4f;
	inline static const float s_GlowRadius = 0.8f;
	
	inline static const Chaos::CircleProps s_CollectibleProps = { Color::Yellow, Color::Black, 1.5f, 0.3f, {0.0f, 0.0f}, 0.0f };

	inline static const Chaos::CircleProps s_GlowProps = { 
		{ Color::Yellow.r, Color::Yellow.g, Color::Yellow.b, 0.05f },
		{ Color::Yellow.r, Color::Yellow.g, Color::Yellow.b, 0.025f },
		3.0f, 0.1f, { 0.0f, 0.0f }, 0.0f 
	};
};