#pragma once

#include "Chaos.h"

#include "ECS/World.h"

void UpdateDamageImpactEffectSystem(World& world, Chaos::Timestep ts);
void UpdateHealthSystem(World& world, Chaos::Timestep ts);