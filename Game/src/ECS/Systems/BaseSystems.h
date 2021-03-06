#pragma once

#include "Chaos.h"

#include "ECS/World.h"

void UpdateFollowSystem(World& world, Chaos::Timestep ts);
void UpdateDestroySystem(World& world, Chaos::Timestep ts);