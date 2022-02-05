#pragma once

#include "Chaos.h"

#include "Constants.h"
#include "VFX.h"

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

struct HealthBarComponent
{
	float Radius = 1.0f;
	float Thickness = 0.2f;
	float BackgroundThickness = 0.4f;
	glm::vec4 Color = Color::Green;

	HealthBarComponent() = default;
	HealthBarComponent(const HealthBarComponent&) = default;
	HealthBarComponent(float radius, float thickness, float backgroundThickness, const glm::vec4& color = Color::Green)
		: Radius(radius), Thickness(thickness), BackgroundThickness(backgroundThickness), Color(color) {}
};

struct TrailEffectComponent
{
	glm::vec2 LastPosition = { 0.0f, 0.0f };
	float Remainder = 0.0f;
	float Distance = 0.0f;

	VFX::TrailEffect TrailEffect = VFX::TrailEffect::Create();

	TrailEffectComponent() = default;
	TrailEffectComponent(const TrailEffectComponent&) = default;
	TrailEffectComponent(const glm::vec2& lastPosition, const VFX::TrailEffect& trailEffect)
		: LastPosition(lastPosition), TrailEffect(trailEffect) {}
};

struct ImpactEffectComponent
{
	// How often can the effect occur in seconds
	float Cooldown = 0.2f;

	// Time left to another effect occurence (0 means its ready)
	float TimeLeft = 0.0f;

	VFX::BurstEffect ImpactEffect = VFX::BurstEffect::Create();

	ImpactEffectComponent() = default;
	ImpactEffectComponent(const ImpactEffectComponent&) = default;
	ImpactEffectComponent(float cooldown, const VFX::BurstEffect& impactEffect)
		: Cooldown(cooldown), ImpactEffect(impactEffect) {}
};

struct DestroyEffectComponent
{
	VFX::BurstEffect DestroyEffect = VFX::BurstEffect::Create();

	DestroyEffectComponent() = default;
	DestroyEffectComponent(const DestroyEffectComponent&) = default;
	DestroyEffectComponent(const VFX::BurstEffect& destroyEffect)
		: DestroyEffect(destroyEffect) {}
};