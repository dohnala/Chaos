#include "pch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Chaos
{
	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_Window(window)
	{
		CH_CORE_ASSERT(window, "Window is null!")
	}

	void OpenGLContext::Init()
	{

		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CH_CORE_ASSERT(status, "Failed to initialize Glad!");

		CH_CORE_INFO("OpenGL Info:");
		CH_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		CH_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		CH_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

		CH_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Chaos requires at least OpenGL version 4.5!");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}
}