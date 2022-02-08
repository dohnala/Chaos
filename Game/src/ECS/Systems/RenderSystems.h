#pragma once

#include "Chaos.h"

#include "ECS/World.h"

void UpdateCircleGlowRenderSystem(World& world, Chaos::Timestep ts);
void UpdateCircleRenderSystem(World& world, Chaos::Timestep ts);
void UpdateAimIndicatorRenderSystem(World& world, Chaos::Timestep ts);
void UpdateHealthBarRenderSystem(World& world, Chaos::Timestep ts);

// Particle systems
void UpdateTrailEffectRenderSystem(World& world, Chaos::Timestep ts);
void UpdateImpactEffectSystem(World& world, Chaos::Timestep ts);
void UpdateParticleEffectRenderSystem(World& world, Chaos::Timestep ts);