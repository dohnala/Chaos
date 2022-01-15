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
	inline static const Chaos::ParticleProps CollectParticleProps = Chaos::ParticleProps::Create()
		.WithDirectionVariance(glm::radians(360.0f))
		.WithSpeed(3.0f, 6.0f)
		.WithSize(0.1f, 0.05f)
		.WithColor(Color::Yellow)
		.WithAlpha(0.5f, 1.0f, 0.0f)
		.WithLifeTime(1.0f, 1.0f);

	inline static uint32_t CollectParticleCount = 10;
private:
	inline static const float s_Radius = 0.4f;
	inline static const float s_GlowRadius = 0.8f;
	
	inline static const Chaos::CircleProps s_CollectibleProps = Chaos::CircleProps::Create()
		.WithColorGradient(Color::Yellow, Color::Black, 1.5f)
		.WithBorderDistortion(0.3f);

	inline static const Chaos::CircleProps s_GlowProps = Chaos::CircleProps::Create()
		.WithColorGradient(Color::WithAlpha(Color::Yellow, 0.05f), Color::WithAlpha(Color::Yellow, 0.025f), 3.0f)
		.WithBorderDistortion(0.1f);
};