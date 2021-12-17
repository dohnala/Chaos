#include "pch.h"
#include "Chaos/Renderer/Buffer.h"
#include "Chaos/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Chaos
{
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::API::None:    CH_CORE_ASSERT(false, "GraphicsAPI::None is currently not supported!"); return nullptr;
			case GraphicsAPI::API::OpenGL:  return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}

		CH_CORE_ASSERT(false, "Unknown GraphicsAPI!");
		return nullptr;
	}
}