#pragma once

#include "Chaos.h"
#include "Color.h"
#include "Entities/CircleEntity.h"
#include "Entities/Projectile.h"

class Player : public CircleEntity
{
public:
	void Init(const glm::vec2& position);

	virtual void OnUpdate(Chaos::Timestep ts) override;
	virtual void OnRender() const override;

	virtual const float GetRadius() const override { return m_BorderRadius; }

	Projectile& GetProjectile() { return m_Projectile; }
private:
	glm::vec2 GetMoveDirection() const;
	void FireProjectile(const glm::vec2& target);
private:
	// Appearance
	const float m_BorderRadius = 1.0f;
	const float m_Radius = 0.6f;
	Chaos::CircleProps m_BorderProps = { Color::Grey, Color::Black, 1.5f, 0.1f, {0.0f, 0.0f}, 0.0f };
	Chaos::CircleProps m_CircleProps = { Color::Blue, Color::Black, 1.5f, 0.3f, {0.0f, 0.0f}, 0.0f };

	// Physics
	const float m_MaxSpeed = 15.0f;
	glm::vec2 m_Velocity;

	Projectile m_Projectile = { 0.45f, 30.0f, { Color::Yellow, Color::Red, 1.0f, 0.4f, { 30.0f, 30.0f }, 3.0f } };
};