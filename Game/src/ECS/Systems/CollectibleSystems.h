#pragma once

#include "Chaos.h"

#include "ECS/World.h"

void UpdateCollectibleFollowSystem(World& world, Chaos::Timestep ts);
void UpdateCollectibleCollisionSystem(World& world, Chaos::Timestep ts);