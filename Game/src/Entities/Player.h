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

	virtual const float GetRadius() const override { return m_BorderRadius; }
private:
	glm::vec2 GetMoveDirection() const;
private:
	// Appearance
	const float m_BorderRadius = 1.0f;
	const float m_Radius = 0.6f;
	Chaos::CircleProps m_BorderProps = { Color::Grey, Color::Black, 1.5f, 0.1f, {0.0f, 0.0f}, 0.0f };
	Chaos::CircleProps m_circleProps = { Color::Blue, Color::Black, 1.5f, 0.3f, {0.0f, 0.0f}, 0.0f };

	// Physics
	const float m_MaxSpeed = 15.0f;
	glm::vec2 m_Velocity;
};