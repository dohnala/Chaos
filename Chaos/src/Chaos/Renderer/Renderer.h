#pragma once

#include "Chaos/Core/Timestep.h"
#include "Chaos/Renderer/Camera.h"
#include "Chaos/Renderer/GraphicsAPI.h"
#include "Chaos/Renderer/OrthographicCamera.h"

namespace Chaos
{
	class CircleProps
	{
	public:
		friend class CirclePropsBuilder;

		static CirclePropsBuilder Create();
	public:
		// Controls the color
		glm::vec4 Color = { 1.0f, 1.0f , 1.0f , 1.0f };
	private:
		CircleProps() = default;
	};

	class CirclePropsBuilder
	{
	public:
		CirclePropsBuilder& WithColor(const glm::vec4& color)
		{
			m_CircleProps.Color = color;
			return *this;
		}

		operator CircleProps && ()
		{
			return std::move(m_CircleProps);
		}
	private:
		CircleProps m_CircleProps;
	};

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void Resize(uint32_t width, uint32_t height);

		static void SetClearColor(const glm::vec4& color);
		static void Clear();

		static void BeginScene(const Camera& camera, const glm::vec2& cameraPosition, Timestep ts);
		static void EndScene();

		static void DrawRect(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawCircle(const glm::vec2& position, float radius, const CircleProps& circleProps);

		static GraphicsAPI::API GetAPI() { return s_GraphicsAPI->GetAPI(); }
	private:
	private:
		static Scope<GraphicsAPI> s_GraphicsAPI;
	};
}