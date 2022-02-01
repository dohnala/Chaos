#pragma once

#include "Chaos.h"

#include "ECS/World.h"
#include "ECS/Components/Components.h"

void UpdateCollectibleFollowSystem(World& world, Chaos::Timestep ts);
void UpdateCollectibleCollisionSystem(World& world, Chaos::Timestep ts);