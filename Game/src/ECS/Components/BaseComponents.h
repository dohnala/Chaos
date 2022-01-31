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

struct FollowComponent
{
	Chaos::Entity Entity;

	FollowComponent() = default;
	FollowComponent(const FollowComponent&) = default;
	FollowComponent(Chaos::Entity entity)
		: Entity(entity) {}
};

struct AimComponent
{
	glm::vec2 Direction = { 0.0f, 0.0f };

	AimComponent() = default;
	AimComponent(const AimComponent&) = default;
};