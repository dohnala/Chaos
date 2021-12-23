#include "Entities/Collectible.h"

void Collectible::OnRender() const
{
	Chaos::Renderer::DrawCircle(m_Position, s_Radius, s_Color, s_InnerRadiusPerc, s_OuterAlpha);
}