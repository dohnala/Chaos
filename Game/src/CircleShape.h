#pragma once

#include <glm/glm.hpp>

class CircleShape
{
public:
	virtual const glm::vec2& GetPosition() const = 0;
	
	// Radius of the circle used for collision detection
	virtual const float GetRadius() const = 0;

	// Radius of the circle as it is displayed
	virtual const float GetDisplayRadius() const = 0;
};