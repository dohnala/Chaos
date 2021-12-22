#pragma once

#include "Chaos.h"
#include "Color.h"

class Player
{
public:
	void Init(const glm::vec2& position);

	void OnUpdate(Chaos::Timestep ts);
	void OnRender();

	const glm::vec2& GetPosition() const { return m_Position; }
	const float GetRadius() const { return m_Radius * m_InnerRadiusPerc; }
private:
	glm::vec2 GetMoveDirection() const;
private:
	// Appearance
	const float m_Radius = 2.0f;
	const float m_InnerRadiusPerc = 0.6f;
	const float m_OuterAlpha = 0.2f;
	const glm::vec4 m_Color = Color::Green;

	// Physics
	const float m_MaxSpeed = 10.0f;
	glm::vec2 m_Velocity;
private:
	glm::vec2 m_Position;
};