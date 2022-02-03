#pragma once

#include "Chaos.h"

#include "ECS/World.h"

void UpdateSkillCooldownSystem(World& world, Chaos::Timestep ts);
void UpdateProjectileSkillSystem(World& world, Chaos::Timestep ts);