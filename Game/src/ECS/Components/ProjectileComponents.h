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

// Change direction of projectile to target in given cone which matches the mask
struct HomingProjectileComponent
{
	// Max distance between projectile and target
	float Distance = 10.0f;
	
	// Max angle between current projectile direction and target in degrees
	float Angle = 15.0;
	
	// Mask to filter entities which should be targeted
	LayerMask TargetMask = Layer::None;

	HomingProjectileComponent() = default;
	HomingProjectileComponent(const HomingProjectileComponent&) = default;
	HomingProjectileComponent(float distance, float angle, LayerMask targetMask)
		: Distance(distance), Angle(angle), TargetMask(targetMask) {}
};