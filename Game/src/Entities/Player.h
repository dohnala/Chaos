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

	Chaos::CircleProps m_BorderProps = Chaos::CircleProps::Create()
		.WithColorGradient(Color::Grey, Color::Black, 1.5f)
		.WithBorderDistortion(0.1f);

	Chaos::CircleProps m_CircleProps = Chaos::CircleProps::Create()
		.WithColorGradient(Color::Blue, Color::Black, 1.5f)
		.WithBorderDistortion(0.3f);

	// Physics
	const float m_MaxSpeed = 15.0f;
	glm::vec2 m_Velocity;

	Projectile m_Projectile = Projectiles::Fireball;
};