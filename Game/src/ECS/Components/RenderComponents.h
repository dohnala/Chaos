#pragma once

#include "Chaos.h"

#include "Effect.h"

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

struct AimIndicatorComponent
{
	// Distance of the indicator from the center
	float Distance = 1.0f;

	// Size of the indicator
	float Size = 0.1f;

	// Props of the circle indicator
	Chaos::PolygonProps PolygonProps = Chaos::PolygonProps::Create();

	AimIndicatorComponent() = default;
	AimIndicatorComponent(const AimIndicatorComponent&) = default;
	AimIndicatorComponent(float distance, float size, const Chaos::PolygonProps& polygonProps)
		: Distance(distance), Size(size), PolygonProps(polygonProps) {}
};

struct TrailEffectComponent
{
	Effect::TrailEffect TrailEffect = Effect::TrailEffect::Create();
	glm::vec2 LastPosition = { 0.0f, 0.0f };
	float Remainder = 0.0f;
	float Distance = 0.0f;

	TrailEffectComponent() = default;
	TrailEffectComponent(const TrailEffectComponent&) = default;
	TrailEffectComponent(const glm::vec2& lastPosition, const Effect::TrailEffect& trailEffect)
		: LastPosition(lastPosition), TrailEffect(trailEffect) {}
};

struct ImpactEffectComponent
{
	uint32_t ParticleCount = 10;
	Chaos::ParticleProps ParticleProps = Chaos::ParticleProps::Create();

	// How often can the effect occur in seconds
	float Cooldown = 0.2f;

	// Time left to another effect occurence (0 means its ready)
	float TimeLeft = 0.0f;

	ImpactEffectComponent() = default;
	ImpactEffectComponent(const ImpactEffectComponent&) = default;
	ImpactEffectComponent(uint32_t particleCount, const Chaos::ParticleProps& particleProps, float cooldown = 0.2f)
		: ParticleCount(particleCount), ParticleProps(particleProps), Cooldown(cooldown) {}
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