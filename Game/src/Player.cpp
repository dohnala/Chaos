#include "Player.h"

void Player::Init(const glm::vec2& position)
{
	m_Position = position;
	m_Velocity = { 0.0f, 0.0f };
}

void Player::OnUpdate(Chaos::Timestep ts)
{
	glm::vec2 direction = GetMoveDirection();
	m_Velocity = direction * m_MaxSpeed;
	m_Position += m_Velocity * (float)ts;
}

void Player::OnRender()
{
	Chaos::Renderer::DrawCircle(m_Position, m_Radius, m_Color, m_InnerRadiusPerc, m_OuterAlpha);
	
}

glm::vec2 Player::GetMoveDirection() const
{
	glm::vec2 direction(0.0f, 0.0f);

	if (Chaos::Input::IsKeyPressed(Chaos::Key::D))
	{
		direction.x += 1;
	}

	if (Chaos::Input::IsKeyPressed(Chaos::Key::A))
	{
		direction.x -= 1;
	}

	if (Chaos::Input::IsKeyPressed(Chaos::Key::W))
	{
		direction.y += 1;
	}

	if (Chaos::Input::IsKeyPressed(Chaos::Key::S))
	{
		direction.y -= 1;
	}

	return direction;
}