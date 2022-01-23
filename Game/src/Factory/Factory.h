#pragma once

#include "Chaos.h"

#include "ECS/World.h"
#include "ECS/Components/Components.h"

class Factory
{
public:
	static Chaos::Entity CreatePlayer(World& world);
	static Chaos::Entity CreateCamera(World& world, Chaos::Entity player);
	static Chaos::Entity CreateCollectible(World& world);
	static Chaos::Entity CreateSkill(World& world, SkillID skill, Chaos::Entity owner);
};