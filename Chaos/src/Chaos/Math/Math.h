#pragma once

#include <glm/glm.hpp>

namespace Chaos::Math
{
	float Damp(float value, float damp, float deltaTime);
	glm::vec2 Damp(const glm::vec2& value, float damp, float deltaTime);

	glm::vec2 PerpendicularClockwise(const glm::vec2& vec);
	glm::vec2 PerpendicularCounterClockwise(const glm::vec2& vec);
}