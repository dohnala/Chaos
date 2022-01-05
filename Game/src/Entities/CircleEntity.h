#pragma once

#include "Chaos.h"

#include <glm/glm.hpp>

class CircleEntity : public Chaos::Entity
{
public:
	virtual const float GetRadius() const = 0;
};