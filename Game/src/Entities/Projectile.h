#pragma once

#include "Chaos.h"
#include "Color.h"
#include "Entities/CircleEntity.h"

class Projectile : public CircleEntity
{
public:
	friend class ProjectileBuilder;

	static ProjectileBuilder Create();

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
	Chaos::ParticleProps ExplosionParticleProps = Chaos::ParticleProps::Create();
	uint32_t ExplosionParticleCount = 0;
	Chaos::ParticleProps TrailParticleProps = Chaos::ParticleProps::Create();
	float TrailParticleCountPerUnit = 0.0f;
private:
	Projectile() = default;
private:
	float m_Radius = 0.5f;
	float m_Speed = 10.0f;
	glm::vec2 m_OldPosition = { 0.0f, 0.0f };
	Chaos::CircleProps m_CircleProps = Chaos::CircleProps::Create();
	glm::vec2 m_Direction = { 0.0f, 0.0f };
	bool m_Active = false;
};

class ProjectileBuilder
{
public:
	ProjectileBuilder& WithRadius(float radius)
	{
		m_Projectile.m_Radius = radius;
		return *this;
	}
	ProjectileBuilder& WithSpeed(float speed)
	{
		m_Projectile.m_Speed = speed;
		return *this;
	}

	ProjectileBuilder& WithCircleRenderer(const Chaos::CircleProps& circleProps)
	{
		m_Projectile.m_CircleProps = circleProps;
		return *this;
	}

	ProjectileBuilder& WithExplosionEffect(const Chaos::ParticleProps& particleProps, uint32_t particleCount)
	{
		m_Projectile.ExplosionParticleProps = particleProps;
		m_Projectile.ExplosionParticleCount = particleCount;
		return *this;
	}

	ProjectileBuilder& WithTrailEffect(const Chaos::ParticleProps& particleProps, float particleCountPerUnit)
	{
		m_Projectile.TrailParticleProps = particleProps;
		m_Projectile.TrailParticleCountPerUnit = particleCountPerUnit;
		return *this;
	}

	operator Projectile && ()
	{
		return std::move(m_Projectile);
	}
private:
	Projectile m_Projectile;
};

namespace Projectiles
{
	inline static Projectile Fireball = Projectile::Create()
		.WithRadius(0.45f)
		.WithSpeed(45.0f)
		.WithCircleRenderer(Chaos::CircleProps::Create()
			.WithColorGradient(Color::Yellow, Color::Red, 1.0f)
			.WithBorderDistortion(0.4f)
			.WithDirectionDistortion(3.0f))
		.WithTrailEffect(Chaos::ParticleProps::Create()
			.WithPositionVariance(0.1f)
			.WithDirectionVariance(glm::radians(90.0f))
			.WithSpeed(0.25f, 0.5f)
			.WithSize(0.1f, 0.05f)
			.WithColorGradient(Color::Yellow, Color::Red)
			.WithAlpha(0.75f, 0.5f, 0.0f)
			.WithLifeTime(0.25f, 0.5f),
			8.0f)
		.WithExplosionEffect(Chaos::ParticleProps::Create()
			.WithDirectionVariance(glm::radians(120.0f))
			.WithSpeed(1.0f, 2.0f)
			.WithSize(0.1f, 0.05f)
			.WithColorGradient(Color::Yellow, Color::Red)
			.WithAlpha(0.75f, 0.5f, 0.0f)
			.WithLifeTime(2.0f, 1.0f),
			20);

	inline static Projectile PoisonBolt = Projectile::Create()
		.WithRadius(0.45f)
		.WithSpeed(45.0f)
		.WithCircleRenderer(Chaos::CircleProps::Create()
			.WithColorGradient(Color::Yellow, Color::Green, 1.5f)
			.WithBorderDistortion(0.4f)
			.WithDirectionDistortion(3.0f))
		.WithTrailEffect(Chaos::ParticleProps::Create()
			.WithPositionVariance(0.1f)
			.WithDirectionVariance(glm::radians(90.0f))
			.WithSpeed(0.25f, 0.5f)
			.WithSize(0.1f, 0.05f)
			.WithColorGradient(Color::Yellow, Color::Green)
			.WithAlpha(0.75f, 0.5f, 0.0f)
			.WithLifeTime(0.25f, 0.5f),
			8.0f)
		.WithExplosionEffect(Chaos::ParticleProps::Create()
			.WithDirectionVariance(glm::radians(120.0f))
			.WithSpeed(1.0f, 2.0f)
			.WithSize(0.1f, 0.05f)
			.WithColorGradient(Color::Yellow, Color::Green)
			.WithAlpha(0.75f, 0.5f, 0.0f)
			.WithLifeTime(2.0f, 1.0f),
			20);
}