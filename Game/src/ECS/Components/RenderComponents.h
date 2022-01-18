#pragma once

#include "Chaos.h"

struct CircleGlowComponent
{
	float Radius = 1.0f;
	Chaos::CircleProps CircleProps = Chaos::CircleProps::Create();

	CircleGlowComponent() = default;
	CircleGlowComponent(const CircleGlowComponent&) = default;
	CircleGlowComponent(float radius, const Chaos::CircleProps& circleProps)
		: Radius(radius), CircleProps(circleProps) {}
};

struct CircleShieldComponent
{
	float Radius = 1.0f;
	Chaos::CircleProps CircleProps = Chaos::CircleProps::Create();

	CircleShieldComponent() = default;
	CircleShieldComponent(const CircleShieldComponent&) = default;
	CircleShieldComponent(float radius, const Chaos::CircleProps& circleProps)
		: Radius(radius), CircleProps(circleProps) {}
};

struct CircleComponent
{
	float Radius = 1.0f;
	Chaos::CircleProps CircleProps = Chaos::CircleProps::Create();

	CircleComponent() = default;
	CircleComponent(const CircleComponent&) = default;
	CircleComponent(float radius, const Chaos::CircleProps& circleProps)
		: Radius(radius), CircleProps(circleProps) {}
};

struct DestroyEffectComponent
{
	uint32_t ParticleCount = 10;
	Chaos::ParticleProps ParticleProps = Chaos::ParticleProps::Create();

	DestroyEffectComponent() = default;
	DestroyEffectComponent(const DestroyEffectComponent&) = default;
	DestroyEffectComponent(uint32_t particleCount, const Chaos::ParticleProps& particleProps)
		: ParticleCount(particleCount), ParticleProps(particleProps) {}
};