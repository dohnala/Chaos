#pragma once

#include "Chaos/Core/KeyCodes.h"
#include "Chaos/Core/MouseCodes.h"

namespace Chaos
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static float GetMouseX();
		static float GetMouseY();
	};
}