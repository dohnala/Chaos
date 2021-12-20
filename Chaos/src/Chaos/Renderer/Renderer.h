#pragma once

#include "Chaos/Renderer/GraphicsAPI.h"

namespace Chaos
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void Resize(uint32_t width, uint32_t height);

		static void SetClearColor(const glm::vec4& color);
		static void Clear();

		static void DrawRect(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawRotatedRect(const glm::vec2& position, float rotation, const glm::vec2& size, const glm::vec4& color);

		static GraphicsAPI::API GetAPI() { return s_GraphicsAPI->GetAPI(); }
	private:
		static void DrawRect(const glm::mat4& transform, const glm::vec4& color);
	private:
		static Scope<GraphicsAPI> s_GraphicsAPI;
	};
}