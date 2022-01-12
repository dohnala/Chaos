#pragma once

#include "Chaos.h"
#include "Color.h"
#include "Entities/CircleEntity.h"

class Projectile : public CircleEntity
{
public:
	Projectile(float radius, float speed, const Chaos::CircleProps& circleProps);

	virtual void OnUpdate(Chaos::Timestep ts) override;
	virtual void OnRender() const override;

	virtual const float GetRadius() const override { return m_Radius; }

	const glm::vec2& GetDirection() const { return m_Direction; }
	void SetDirection(const glm::vec2& direction) { m_Direction = direction; m_CircleProps.Direction = direction; }
	
	bool IsEnabled() const { return m_Active; }
	void Show() { m_Active = true; }
	void Destroy() { m_Active = false; }
private:
	float m_Radius;
	float m_Speed;
	Chaos::CircleProps m_CircleProps;
	glm::vec2 m_Direction;
	bool m_Active = false;
};