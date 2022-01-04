#pragma once

#include "Chaos.h"
#include "Color.h"
#include "Entities/CircleEntity.h"

class Collectible : public CircleEntity
{
public:
	virtual void OnRender() const override;

	virtual const float GetColliderRadius() const override { return s_Radius * s_InnerRadiusPerc; }
	virtual const float GetRenderRadius() const override { return s_Radius; };
public:
	// Appearance
	inline static const float s_Radius = 0.5f;
	inline static const float s_InnerRadiusPerc = 0.5f;
	inline static const float s_OuterAlpha = 0.05f;
	inline static glm::vec4 s_Color = Color::Yellow;
};