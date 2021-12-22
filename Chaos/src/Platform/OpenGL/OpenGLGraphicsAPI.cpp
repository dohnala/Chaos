#include "pch.h"
#include "Platform/OpenGL/OpenGLGraphicsAPI.h"

#include <glad/glad.h>

namespace Chaos
{
	void OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam)
	{
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:         CH_CORE_ERROR(message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:       CH_CORE_ERROR(message); return;
			case GL_DEBUG_SEVERITY_LOW:          CH_CORE_WARN(message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: CH_CORE_TRACE(message); return;
		}

		CH_CORE_ASSERT(false, "Unknown severity level!");
	}

	void OpenGLGraphicsAPI::Init()
	{
		#ifdef CH_DEBUG
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(OpenGLMessageCallback, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
		#endif

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLGraphicsAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLGraphicsAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLGraphicsAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLGraphicsAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}