#include "ECS/Systems/InputSystems.h"

#include <glm/glm.hpp>

void UpdateInputMovementSystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [entityID, kbComp, moveComp] : world.View<KeybindingsComponent, MoveComponent>().each())
	{
		glm::vec2 direction(0.0f, 0.0f);

		if (Chaos::Input::IsKeyPressed(kbComp.Right))
		{
			direction.x += 1;
		}

		if (Chaos::Input::IsKeyPressed(kbComp.Left))
		{
			direction.x -= 1;
		}

		if (Chaos::Input::IsKeyPressed(kbComp.Up))
		{
			direction.y += 1;
		}

		if (Chaos::Input::IsKeyPressed(kbComp.Down))
		{
			direction.y -= 1;
		}

		moveComp.Direction = direction;
	}
}