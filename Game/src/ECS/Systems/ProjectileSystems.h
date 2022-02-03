#pragma once

#include "Chaos.h"

#include "ECS/World.h"

void UpdateHomingProjectileSystem(World& world, Chaos::Timestep ts);
void UpdateProjectileCollisionSystem(World& world, Chaos::Timestep ts);