#pragma once

#include "Chaos.h"

#include <glm/glm.hpp>

struct PositionComponent
{
	glm::vec2 Position = { 0.0f, 0.0f };

	PositionComponent() = default;
	PositionComponent(const PositionComponent&) = default;
	PositionComponent(const glm::vec2& position)
		: Position(position) {}
};

struct CameraComponent
{
	Chaos::OrthographicCamera Camera;

	CameraComponent() = default;
	CameraComponent(const CameraComponent&) = default;
};

// Entities with this component will be destroyed after given delay
struct DestroyComponent
{
	float Delay = 0.0f;

	DestroyComponent() = default;
	DestroyComponent(const DestroyComponent&) = default;
	DestroyComponent(float delay = 0.0f)
		: Delay(delay) {}
};

// Follow given entity with a damp based on the distance between the entity
struct FollowComponent
{
	Chaos::Entity Entity;
	float DampMin = 1.0;
	float DampMax = 1.0;
	float Distance = 0.0f;

	FollowComponent() = default;
	FollowComponent(const FollowComponent&) = default;
	FollowComponent(Chaos::Entity entity, float dampMin = 1.0f, float dampMax = 1.0f, float distance = 0.0f)
		: Entity(entity), DampMin(dampMin), DampMax(dampMax), Distance(distance) {}
};

struct AimComponent
{
	glm::vec2 Direction = { 0.0f, 0.0f };

	AimComponent() = default;
	AimComponent(const AimComponent&) = default;
};

struct HealthComponent
{
	float Health = 5.0f;
	float MaxHealth = 5.0f;

	HealthComponent() = default;
	HealthComponent(const HealthComponent&) = default;
	HealthComponent(float health, float maxHealth)
		: Health(health), MaxHealth(maxHealth) {}
};