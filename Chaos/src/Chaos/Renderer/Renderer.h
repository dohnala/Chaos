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

		static void DrawRect();

		static GraphicsAPI::API GetAPI() { return s_GraphicsAPI->GetAPI(); }
	private:
		static Scope<GraphicsAPI> s_GraphicsAPI;
	};
}