#pragma once

#include <glm/glm.hpp>

namespace Chaos::Math
{
	float Damp(float value, float damp, float deltaTime);
	glm::vec2 Damp(const glm::vec2& value, float damp, float deltaTime);
}