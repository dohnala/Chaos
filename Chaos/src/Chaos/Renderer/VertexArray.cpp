#include "pch.h"
#include "Chaos/Renderer/VertexArray.h"
#include "Chaos/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Chaos
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::API::None:    CH_CORE_ASSERT(false, "GraphicsAPI::None is currently not supported!"); return nullptr;
			case GraphicsAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
		}

		CH_CORE_ASSERT(false, "Unknown GraphicsAPI!");
		return nullptr;
	}
}