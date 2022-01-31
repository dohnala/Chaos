#pragma once

#include "Chaos.h"

#include "ECS/World.h"

void UpdateInputMovementSystem(World& world, Chaos::Timestep ts);
void UpdateInputAimSystem(World& world, Chaos::Timestep ts);
void UpdateInputSkillSystem(World& world, Chaos::Timestep ts);