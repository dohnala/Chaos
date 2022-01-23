#pragma once

#include "Chaos/Core/KeyCodes.h"
#include "Chaos/Core/MouseCodes.h"

#include <glm/glm.hpp>

namespace Chaos
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
	};
}