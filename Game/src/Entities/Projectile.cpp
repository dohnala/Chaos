#include "Entities/Projectile.h"

Projectile::Projectile(float radius, float speed, 
	const Chaos::CircleProps& circleProps,
	const Chaos::ParticleProps& explosionParticleProps, uint32_t explosionParticleCount,
	const Chaos::ParticleProps& trailParticleProps, float trailParticleCountPerUnit)
	: m_Radius(radius), 
	  m_Speed(speed), 
	  m_CircleProps(circleProps), 
	  ExplosionParticleProps(explosionParticleProps), 
	  ExplosionParticleCount(explosionParticleCount),
	  TrailParticleProps(trailParticleProps),
	  TrailParticleCountPerUnit(trailParticleCountPerUnit)
{}

void Projectile::OnUpdate(Chaos::Timestep ts)
{
	if (m_Active)
	{
		m_OldPosition = m_Position;
		m_Position += m_Direction * m_Speed * ts.GetDeltaTime();
	}
}

void Projectile::OnRender() const
{
	if (m_Active)
	{
		Chaos::Renderer::DrawCircle(m_Position, m_Radius, m_CircleProps);
	}
}