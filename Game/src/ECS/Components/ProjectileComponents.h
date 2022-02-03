#pragma once

#include "Chaos.h"

#include "Constants.h"

struct ProjectileComponent
{
	SkillID Skill;
	Chaos::Entity Owner;

	ProjectileComponent() = default;
	ProjectileComponent(const ProjectileComponent&) = default;
	ProjectileComponent(SkillID skill, Chaos::Entity owner)
		: Skill(skill), Owner(owner) {}
};