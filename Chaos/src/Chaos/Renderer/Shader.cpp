#include "pch.h"
#include "Chaos/Renderer/Shader.h"
#include "Chaos/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Chaos
{
	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::API::None:    CH_CORE_ASSERT(false, "GraphicsAPI::None is currently not supported!"); return nullptr;
			case GraphicsAPI::API::OpenGL:  return CreateScope<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		CH_CORE_ASSERT(false, "Unknown GraphicsAPI!");
		return nullptr;
	}
}