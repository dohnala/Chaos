#pragma once

#include "Chaos.h"

#include "ECS/World.h"

class Factory
{
public:
	static Chaos::Entity CreatePlayer(World& world);
	static Chaos::Entity CreateCamera(World& world, Chaos::Entity player);
	static Chaos::Entity CreateCollectible(World& world);
};