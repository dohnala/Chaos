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
	inline static const float s_Radius = 0.25f;
	inline static const float s_GlowRadius = 0.5f;
	inline static const float s_GlowAlpha = 0.05f;
	inline static glm::vec4 s_Color = Color::Yellow;
};