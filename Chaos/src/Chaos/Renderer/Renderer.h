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

	class PolygonProps
	{
	public:
		friend class PolygonPropsBuilder;

		static PolygonPropsBuilder Create();
	public:
		uint32_t VertexCount = 3;
		glm::vec4 Color = { 1.0f, 1.0f , 1.0f , 1.0f };
	private:
		PolygonProps() = default;
	};

	class PolygonPropsBuilder
	{
	public:
		PolygonPropsBuilder& WithVertexCount(uint32_t vertexCount)
		{
			CH_ASSERT(vertexCount >= 3, "Polygon should have at least 3 vertices!");
			m_PolygonProps.VertexCount = vertexCount;
			return *this;
		}

		PolygonPropsBuilder& WithColor(const glm::vec4& color)
		{
			m_PolygonProps.Color = color;
			return *this;
		}

		operator PolygonProps && ()
		{
			return std::move(m_PolygonProps);
		}
	private:
		PolygonProps m_PolygonProps;
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
		static void DrawPolygon(const glm::vec2& position, const glm::vec2& size, const PolygonProps& polygonProps);
		static void DrawPolygon(const glm::vec2& position, float rotation, const glm::vec2& size, const PolygonProps& polygonProps);

		static GraphicsAPI::API GetAPI() { return s_GraphicsAPI->GetAPI(); }
	private:
		static void DrawPolygon(const glm::mat4& transform, const PolygonProps& polygonProps);
	private:
		static Scope<GraphicsAPI> s_GraphicsAPI;
	};
}