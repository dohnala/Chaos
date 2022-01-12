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
	m_Position += m_Velocity * ts.GetDeltaTime();

	m_BorderProps.Direction = { direction.x, direction.y };
	m_CircleProps.Direction = { direction.x, direction.y };

	if (Chaos::Input::IsMouseButtonPressed(Chaos::Mouse::ButtonLeft))
	{
		FireProjectile();
	}

	m_Projectile.OnUpdate(ts);
}

void Player::OnRender() const
{
	Chaos::Renderer::DrawCircle(m_Position, m_BorderRadius, m_BorderProps);
	Chaos::Renderer::DrawCircle(m_Position, m_Radius, m_CircleProps);

	m_Projectile.OnRender();
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

void Player::FireProjectile()
{
	if (!m_Projectile.IsEnabled())
	{
		m_Projectile.SetPosition(m_Position);
		m_Projectile.SetDirection({ 1.0f, 0.0f });
		m_Projectile.Show();
	}
}