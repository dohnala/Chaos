#pragma once

#include "Chaos.h"

class Player
{
public:
	void Init(const glm::vec2& position);

	void OnUpdate(Chaos::Timestep ts);
	void OnRender();

private:
	glm::vec2 m_Position;
};