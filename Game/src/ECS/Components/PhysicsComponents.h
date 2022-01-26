#pragma once

#include "Chaos.h"

#include <glm/glm.hpp>

struct MoveComponent
{
	glm::vec2 Direction = { 0.0f, 0.0f };
	glm::vec2 Velocity = { 0.0f, 0.0f };

	float Acceleration = 10.0f;
	float MaxSpeed = 10.0f;
	float Friction = 0.5f;

	MoveComponent() = default;
	MoveComponent(const MoveComponent&) = default;
	MoveComponent(float acceleration = 10.0f, float maxSpeed = 10.0f, float friction = 0.5f)
		: Acceleration(acceleration), MaxSpeed(maxSpeed), Friction(friction) {}
};

struct CircleColliderComponent
{
	float Radius = 1.0f;

	CircleColliderComponent() = default;
	CircleColliderComponent(const CircleColliderComponent&) = default;
	CircleColliderComponent(float radius)
		: Radius(radius) {}
};

struct CollisionComponent
{
	Chaos::Entity Entity;
	glm::vec2 Position = { 0.0f, 0.0f };
	glm::vec2 Normal = { 0.0f, 0.0f };

	CollisionComponent() = default;
	CollisionComponent(const CollisionComponent&) = default;
};