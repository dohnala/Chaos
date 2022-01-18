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

struct KeybindingsComponent
{
	uint16_t Up = Chaos::Key::W;
	uint16_t Left = Chaos::Key::A;
	uint16_t Down = Chaos::Key::S;
	uint16_t Right = Chaos::Key::D;

	KeybindingsComponent() = default;
	KeybindingsComponent(const KeybindingsComponent&) = default;
};

struct FollowComponent
{
	Chaos::Entity Entity;

	FollowComponent() = default;
	FollowComponent(const FollowComponent&) = default;
	FollowComponent(Chaos::Entity entity)
		: Entity(entity) {}
};