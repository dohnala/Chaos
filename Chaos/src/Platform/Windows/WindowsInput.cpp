#include "pch.h"
#include "Chaos/Core/Input.h"
#include "Chaos/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Chaos {
	bool Input::IsKeyPressed(const KeyCode key)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		bool isWindowFocused = Application::Get().IsWindowFocused();
		auto state = glfwGetKey(window, static_cast<int32_t>(key));
		return isWindowFocused && (state == GLFW_PRESS || state == GLFW_REPEAT);
	}

	bool Input::IsMouseButtonPressed(const MouseCode button)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		bool isWindowFocused = Application::Get().IsWindowFocused();
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return isWindowFocused && (state == GLFW_PRESS);
	}

	glm::vec2 Input::GetMousePosition()
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}
}