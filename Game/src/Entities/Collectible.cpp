#include "Entities/Collectible.h"

void Collectible::OnRender() const
{
	Chaos::Renderer::DrawCircle(m_Position, s_GlowRadius, { s_Color.r, s_Color.g, s_Color.b, s_GlowAlpha });
	Chaos::Renderer::DrawCircle(m_Position, s_Radius, s_Color);
}