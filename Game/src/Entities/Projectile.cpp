#include "Entities/Projectile.h"

Projectile::Projectile(float radius, float speed, const Chaos::CircleProps& circleProps)
	: m_Radius(radius), m_Speed(speed), m_CircleProps(circleProps)
{}

void Projectile::OnUpdate(Chaos::Timestep ts)
{
	if (m_Active)
	{
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