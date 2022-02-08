#pragma once

#include "Chaos.h"

#include <glm/glm.hpp>

struct HealthComponent
{
	float Health = 5.0f;
	float MaxHealth = 5.0f;

	HealthComponent() = default;
	HealthComponent(const HealthComponent&) = default;
	HealthComponent(float health, float maxHealth)
		: Health(health), MaxHealth(maxHealth) {}
};

struct DamageComponent
{
	float Damage = 0.0f;

	DamageComponent() = default;
	DamageComponent(const DamageComponent&) = default;
	DamageComponent(float damage)
		: Damage(damage) {}
};

struct DamageableComponent
{};

struct ReceivedDamageComponent
{
	Chaos::Entity Source;
	glm::vec2 Position;
	glm::vec2 Direction;
	float Damage;

	ReceivedDamageComponent() = default;
	ReceivedDamageComponent(const ReceivedDamageComponent&) = default;
	ReceivedDamageComponent(Chaos::Entity source, const glm::vec2& position, const glm::vec2& direction, float damage)
		: Source(source), Position(position), Direction(direction), Damage(damage) {}
};