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
	Chaos::ParticleProps ExplosionParticleProps;
	uint32_t ExplosionParticleCount;
	Chaos::ParticleProps TrailParticleProps;
	float TrailParticleCountPerUnit;
private:
	glm::vec2 m_OldPosition;
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
		{ Color::Yellow, Color::Red, 1.0f, 0.4f, { 30.0f, 30.0f }, 3.0f }, // CircleProps
		// ExplosionParticleProps
		{ 
			0.0f,											// PositionRadiusVariance
			{ 0.0f, 1.0f }, glm::radians(120.0f),			// Direction, DirectionAngleVariance
			1.0f, 2.0f,										// Speed, SpeedVariance
			0.1f, 0.05f,									// Size, SizeVariance
			Color::Yellow, Color::Red,						// ColorFrom, ColorTo
			0.75f, 0.5f, 0.0f,								// Alpha, AlphaVariance, AlphaEnd
			2.0f, 1.0f										// LifeTime, LifeTimeVariance
		}, 
		20,	// ExplosionParticleCount
		// TrailParticleProps
		{ 
			0.1f,											// PositionRadiusVariance
			{ 0.0f, 0.0f }, glm::radians(90.0f),			// Direction, DirectionAngleVariance
			0.25f, 0.5f,									// Speed, SpeedVariance
			0.1f, 0.05f,									// Size, SizeVariance
			Color::Yellow, Color::Red,						// ColorFrom, ColorTo
			0.75f, 0.5f, 0.0f,								// Alpha, AlphaVariance, AlphaEnd
			0.25f, 0.5f										// LifeTime, LifeTimeVariance
		},
		8.0f // TrailParticleCountPerUnit
	); 
}