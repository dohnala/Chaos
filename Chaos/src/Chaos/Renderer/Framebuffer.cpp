#include "pch.h"
#include "Chaos/Renderer/Framebuffer.h"
#include "Chaos/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Chaos
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferProps& props)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::API::None:    CH_CORE_ASSERT(false, "GraphicsAPI::None is currently not supported!"); return nullptr;
			case GraphicsAPI::API::OpenGL:  return CreateRef<OpenGLFramebuffer>(props);
		}

		CH_CORE_ASSERT(false, "Unknown GraphicsAPI!");
		return nullptr;
	}
}