#pragma once

#include "Chaos.h"

#include "ECS/World.h"
#include "ECS/Components/Components.h"

void UpdateSkillCooldownSystem(World& world, Chaos::Timestep ts);
void UpdateProjectileSkillSystem(World& world, Chaos::Timestep ts);
void UpdateProjectileDestroySystem(World& world, Chaos::Timestep ts);