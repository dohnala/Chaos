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
	// Appearance
	inline static const float s_Radius = 0.4f;
	inline static const float s_GlowRadius = 0.8f;

	inline static const Chaos::CircleProps s_CollectibleProps = { Color::Yellow, Color::Black, 1.5f, 0.0f, {0.0f, 0.0f}, 0.0f };
	inline static const Chaos::CircleProps s_GlowProps = { 
		{ Color::Yellow.r, Color::Yellow.g, Color::Yellow.b, 0.05f },
		{ Color::Yellow.r, Color::Yellow.g, Color::Yellow.b, 0.05f },
		1.0f, 0.0f, { 0.0f, 0.0f }, 0.0f 
	};
};