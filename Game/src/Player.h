#pragma once

#include "Chaos.h"
#include "Color.h"
#include "CircleShape.h"

class Player : public CircleShape
{
public:
	void Init(const glm::vec2& position);

	void OnUpdate(Chaos::Timestep ts);
	void OnRender();

	virtual const glm::vec2& GetPosition() const override { return m_Position; }
	virtual const float GetRadius() const override { return m_Radius * m_InnerRadiusPerc; }
private:
	glm::vec2 GetMoveDirection() const;
private:
	// Appearance
	const float m_Radius = 1.0f;
	const float m_InnerRadiusPerc = 0.6f;
	const float m_OuterAlpha = 0.2f;
	const glm::vec4 m_Color = Color::Green;

	// Physics
	const float m_MaxSpeed = 10.0f;
	glm::vec2 m_Velocity;
	glm::vec2 m_Position;
};