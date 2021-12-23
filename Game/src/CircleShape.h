#pragma once

#include "Chaos.h"

#include <glm/glm.hpp>

class CircleShape : public Chaos::Entity
{
public:
	// Radius of the circle used for collision detection
	virtual const float GetRadius() const = 0;

	// Radius of the circle as it is displayed
	virtual const float GetDisplayRadius() const = 0;
};