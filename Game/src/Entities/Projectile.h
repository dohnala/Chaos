#pragma once

#include "Chaos.h"
#include "Color.h"
#include "Entities/CircleEntity.h"

class Projectile : public CircleEntity
{
public:
	Projectile(float radius, float speed, 
		const Chaos::CircleProps& circleProps,
		const Chaos::ParticleProps& explosionParticleProps, uint32_t explosionParticleCount,
		const Chaos::ParticleProps& trailParticleProps, float trailParticleCountPerUnit);

	virtual void OnUpdate(Chaos::Timestep ts) override;
	virtual void OnRender() const override;

	const glm::vec2& GetOldPosition() const { return m_OldPosition; };

	virtual const float GetRadius() const override { return m_Radius; }

	const glm::vec2& GetDirection() const { return m_Direction; }
	void SetDirection(const glm::vec2& direction) { m_Direction = direction; m_CircleProps.Direction = direction; }
	
	bool IsEnabled() const { return m_Active; }
	void Show() { m_Active = true; }
	void Destroy() { m_Active = false; }
public:
	const Chaos::ParticleProps ExplosionParticleProps;
	const uint32_t ExplosionParticleCount;
	const Chaos::ParticleProps TrailParticleProps;
	const float TrailParticleCountPerUnit;
private:
	glm::vec2 m_OldPosition = { 0.0f, 0.0f };
	float m_Radius;
	float m_Speed;
	Chaos::CircleProps m_CircleProps;
	glm::vec2 m_Direction = { 0.0f, 0.0f };
	bool m_Active = false;
};

namespace Projectiles
{
	inline static Projectile Fireball = Projectile(
		0.45f, // Radius
		45.0f, // Speed
		// CircleProps
		Chaos::CircleProps::Create()
			.WithColorGradient(Color::Yellow, Color::Red, 1.0f)
			.WithBorderDistortion(0.4f)
			.WithDirectionDistortion(3.0f),
		// ExplosionParticleProps
		Chaos::ParticleProps::Create()
			.WithDirectionVariance(glm::radians(120.0f))
			.WithSpeed(1.0f, 2.0f)
			.WithSize(0.1f, 0.05f)
			.WithColorGradient(Color::Yellow, Color::Red)
			.WithAlpha(0.75f, 0.5f, 0.0f)
			.WithLifeTime(2.0f, 1.0f),
		20,	// ExplosionParticleCount
		// TrailParticleProps
		Chaos::ParticleProps::Create()
			.WithPositionVariance(0.1f)
			.WithDirectionVariance(glm::radians(90.0f))
			.WithSpeed(0.25f, 0.5f)
			.WithSize(0.1f, 0.05f)
			.WithColorGradient(Color::Yellow, Color::Red)
			.WithAlpha(0.75f, 0.5f, 0.0f)
			.WithLifeTime(0.25f, 0.5f),
		8.0f // TrailParticleCountPerUnit
	); 
}