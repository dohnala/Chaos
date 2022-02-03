#pragma once

#include "Chaos.h"

#include "Constants.h"
#include "ECS/Components/RenderComponents.h"

struct SkillSlotsComponent
{
	Chaos::Entity SkillSlot1;

	SkillSlotsComponent() = default;
	SkillSlotsComponent(const SkillSlotsComponent&) = default;
};

struct SkillComponent
{
	SkillID Skill;
	Chaos::Entity Owner;
	float Cooldown;

	SkillComponent() = default;
	SkillComponent(const SkillComponent&) = default;
	SkillComponent(SkillID skill, Chaos::Entity owner, float cooldown)
		: Skill(skill), Owner(owner), Cooldown(cooldown) {}
};

struct SkillActiveComponent
{
	float TimeLeft = 0.0f;

	SkillActiveComponent() = default;
	SkillActiveComponent(const SkillActiveComponent&) = default;
	SkillActiveComponent(float timeLeft)
		: TimeLeft(timeLeft) {}
};

struct SkillCooldownComponent
{
	float TimeLeft = 0.0f;

	SkillCooldownComponent() = default;
	SkillCooldownComponent(const SkillCooldownComponent&) = default;
	SkillCooldownComponent(float timeLeft)
		: TimeLeft(timeLeft) {}
};

struct ProjectileSkillComponent
{
	float Radius = 0.5f;
	float Acceleration = 200.0f;
	float MaxSpeed = 50.0f;

	Chaos::CircleProps ProjectileProps = Chaos::CircleProps::Create();
	
	VFX::TrailEffect TrailEffect = VFX::TrailEffect::Create();
	
	Chaos::ParticleProps DestroyEffect = Chaos::ParticleProps::Create();
	uint32_t DestroyEffectCount = 0;

	ProjectileSkillComponent() = default;
	ProjectileSkillComponent(const ProjectileSkillComponent&) = default;
	ProjectileSkillComponent(float radius, float acceleration, float maxSpeed)
		: Radius(radius), Acceleration(acceleration), MaxSpeed(maxSpeed) {}
};