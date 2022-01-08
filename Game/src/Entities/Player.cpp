#include "Player.h"

void Player::Init(const glm::vec2& position)
{
	circleProps.ColorInside = Color::Green;
	circleProps.ColorOutside = Color::Black;
	circleProps.ColorRatio = 1.5f;
	circleProps.BorderDistortion = 0.2f;
	circleProps.DirectionDistortion = 0.0f;

	m_Position = position;
	m_Velocity = { 0.0f, 0.0f };
}

void Player::OnUpdate(Chaos::Timestep ts)
{
	glm::vec2 direction = GetMoveDirection();
	m_Velocity = direction * m_MaxSpeed;
	m_Position += m_Velocity * ts.GetDeltaTime();

	circleProps.Direction = { direction.x, direction.y };
}

void Player::OnRender() const
{
	//Chaos::Renderer::DrawCircle(m_Position, m_GlowRadius, { m_Color.r, m_Color.g, m_Color.b, m_GlowAlpha });
	Chaos::Renderer::DrawCircle(m_Position, m_Radius, circleProps);
	
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