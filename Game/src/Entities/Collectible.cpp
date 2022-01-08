#include "Entities/Collectible.h"

void Collectible::OnRender() const
{
	Chaos::Renderer::DrawCircle(m_Position, s_GlowRadius, s_GlowProps);
	Chaos::Renderer::DrawCircle(m_Position, s_Radius, s_CollectibleProps);
}