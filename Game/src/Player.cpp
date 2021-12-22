#include "Player.h"

void Player::Init(const glm::vec2& position)
{
	m_Position = position;
}

void Player::OnUpdate(Chaos::Timestep ts)
{}

void Player::OnRender()
{
	Chaos::Renderer::DrawCircle(m_Position, m_Radius, m_Color, m_InnerRadiusPerc, m_OuterAlpha);
	
}