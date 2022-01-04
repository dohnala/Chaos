#pragma once

#include "Chaos.h"
#include "Color.h"
#include "Entities/CircleEntity.h"

class Player : public CircleEntity
{
public:
	void Init(const glm::vec2& position);

	virtual void OnUpdate(Chaos::Timestep ts) override;
	virtual void OnRender() const override;

	virtual const float GetColliderRadius() const override { return m_Radius * m_InnerRadiusPerc; }
	virtual const float GetRenderRadius() const override { return m_Radius; };
private:
	glm::vec2 GetMoveDirection() const;
private:
	// Appearance
	const float m_Radius = 1.0f;
	const float m_InnerRadiusPerc = 0.6f;
	const float m_OuterAlpha = 0.05f;
	const glm::vec4 m_Color = Color::Green;

	// Physics
	const float m_MaxSpeed = 10.0f;
	glm::vec2 m_Velocity;
};