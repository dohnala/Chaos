#pragma once

#include "Chaos.h"

#include "ECS/World.h"
#include "ECS/Components/Components.h"

void UpdateMovementSystem(World& world, Chaos::Timestep ts);
void UpdateCollisionSystem(World& world, Chaos::Timestep ts);
void UpdateCameraCollisionSystem(World& world, Chaos::Timestep ts);