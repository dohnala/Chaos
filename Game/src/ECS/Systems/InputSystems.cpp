#include "ECS/Systems/InputSystems.h"
#include "ECS/Components/Components.h"

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
	for (auto&& [entityID, kbComp, moveComp] : world.View<InputComponent, MoveComponent>().each())
	{
		glm::vec2 direction(0.0f, 0.0f);

		if (IsKeybindPressed(kbComp.Right))
		{
			direction.x += 1;
		}

		if (IsKeybindPressed(kbComp.Left))
		{
			direction.x -= 1;
		}

		if (IsKeybindPressed(kbComp.Up))
		{
			direction.y += 1;
		}

		if (IsKeybindPressed(kbComp.Down))
		{
			direction.y -= 1;
		}

		moveComp.Direction = direction;
	}
}

void UpdateInputSkillSystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [entityID, kbComp, skillComp] : world.View<InputComponent, SkillSlotsComponent>().each())
	{
		if (IsKeybindPressed(kbComp.SkillSlot1) && 
			skillComp.SkillSlot1 &&
			!skillComp.SkillSlot1.HasComponent<SkillActiveComponent>() &&
			!skillComp.SkillSlot1.HasComponent<SkillCooldownComponent>())
		{
			skillComp.SkillSlot1.AddComponent<SkillActiveComponent>();
		}
	}
}