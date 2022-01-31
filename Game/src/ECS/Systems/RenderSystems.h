#pragma once

#include "Chaos.h"

#include "ECS/World.h"
#include "ECS/Components/Components.h"

void UpdateCircleGlowRenderSystem(World& world, Chaos::Timestep ts);
void UpdateCircleRenderSystem(World& world, Chaos::Timestep ts);
void UpdateCreatureRenderSystem(World& world, Chaos::Timestep ts);
void UpdateTrailEffectSystem(World& world, Chaos::Timestep ts);
void UpdateImpactEffectSystem(World& world, Chaos::Timestep ts);
void UpdateParticleEffectRenderSystem(World& world, Chaos::Timestep ts);