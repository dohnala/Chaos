#include "Player.h"

void Player::Init(const glm::vec2& position)
{
	m_Position = position;
}

void Player::OnUpdate(Chaos::Timestep ts)
{}

void Player::OnRender()
{
	Chaos::Renderer::DrawCircle(m_Position, 2.0f, { 0.2f, 0.8f, 0.3f, 1.0f }, 0.6f, 0.2f);
	
}