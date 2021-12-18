#pragma once

#include "Chaos/Core/Base.h"
#include "Chaos/Renderer/VertexArray.h"

#include <glm/glm.hpp>

namespace Chaos
{
	class GraphicsAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};

		virtual API GetAPI() const = 0;

		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;
	};
}