#include "Entities/Projectile.h"

ProjectileBuilder Projectile::Create()
{
	return ProjectileBuilder();
}

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