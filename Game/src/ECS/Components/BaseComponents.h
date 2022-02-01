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
	float Damp = 1.0;

	FollowComponent() = default;
	FollowComponent(const FollowComponent&) = default;
	FollowComponent(Chaos::Entity entity, float damp = 1.0f)
		: Entity(entity), Damp(damp) {}
};

struct AimComponent
{
	glm::vec2 Direction = { 0.0f, 0.0f };

	AimComponent() = default;
	AimComponent(const AimComponent&) = default;
};