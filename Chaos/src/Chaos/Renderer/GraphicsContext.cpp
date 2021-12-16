#include "pch.h"
#include "Chaos/Renderer/GraphicsContext.h"
#include "Chaos/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Chaos
{
	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::API::None:    CH_CORE_ASSERT(false, "GraphicsAPI::None is currently not supported!"); return nullptr;
			case GraphicsAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		CH_CORE_ASSERT(false, "Unknown GraphicsAPI!");
		return nullptr;
	}
}