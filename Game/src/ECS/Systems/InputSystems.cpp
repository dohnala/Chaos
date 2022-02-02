#include "ECS/Systems/InputSystems.h"
#include "ECS/Components/BaseComponents.h"
#include "ECS/Components/InputComponents.h"
#include "ECS/Components/PhysicsComponents.h"
#include "ECS/Components/SkillComponents.h"

#include <glm/glm.hpp>

static bool IsKeybindPressed(const Keybind& keyBind)
{
	switch (keyBind.Type)
	{
	case Keybind::Type::Key:
		return Chaos::Input::IsKeyPressed(keyBind.Code);
	case Keybind::Type::Mouse:
		return Chaos::Input::IsMouseButtonPressed(keyBind.Code);
	default:
		return false;
	}
}

void UpdateInputMovementSystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [entityID, inputComp, moveComp] : world.View<InputComponent, MoveComponent>().each())
	{
		glm::vec2 direction(0.0f, 0.0f);

		if (IsKeybindPressed(inputComp.Right))
		{
			direction.x += 1;
		}

		if (IsKeybindPressed(inputComp.Left))
		{
			direction.x -= 1;
		}

		if (IsKeybindPressed(inputComp.Up))
		{
			direction.y += 1;
		}

		if (IsKeybindPressed(inputComp.Down))
		{
			direction.y -= 1;
		}

		moveComp.Direction = direction;
	}
}

void UpdateInputAimSystem(World& world, Chaos::Timestep ts)
{
	auto targetPosition = world.ScreenToWorldPosition(Chaos::Input::GetMousePosition());

	for (auto&& [entityID, inputComp, positionComponent, aimComp] : world.View<InputComponent, PositionComponent, AimComponent>().each())
	{
		aimComp.Direction = glm::normalize(targetPosition - positionComponent.Position);
	}
}

void UpdateInputSkillSystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [entityID, inputComp, skillComp] : world.View<InputComponent, SkillSlotsComponent>().each())
	{
		if (IsKeybindPressed(inputComp.SkillSlot1) &&
			skillComp.SkillSlot1 &&
			!skillComp.SkillSlot1.HasComponent<SkillActiveComponent>() &&
			!skillComp.SkillSlot1.HasComponent<SkillCooldownComponent>())
		{
			skillComp.SkillSlot1.AddComponent<SkillActiveComponent>();
		}
	}
}