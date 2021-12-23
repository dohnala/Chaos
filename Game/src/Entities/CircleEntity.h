#pragma once

#include "Chaos.h"

#include <glm/glm.hpp>

class CircleEntity : public Chaos::Entity
{
public:
	// Radius of the circle used for collision detection
	virtual const float GetColliderRadius() const = 0;

	// Radius of the circle as it is rendered
	virtual const float GetRenderRadius() const = 0;
};