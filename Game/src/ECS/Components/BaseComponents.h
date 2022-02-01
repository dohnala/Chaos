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