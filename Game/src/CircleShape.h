#pragma once

#include <glm/glm.hpp>

class CircleShape
{
public:
	virtual const glm::vec2& GetPosition() const = 0;
	virtual const float GetRadius() const = 0;
};