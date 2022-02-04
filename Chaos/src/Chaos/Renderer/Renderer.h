#pragma once

#include "Chaos/Core/Timestep.h"
#include "Chaos/Renderer/Camera.h"
#include "Chaos/Renderer/GraphicsAPI.h"
#include "Chaos/Renderer/OrthographicCamera.h"

namespace Chaos
{
	struct CircleProps
	{
	public:
		static CircleProps Create()
		{
			return CircleProps();
		}
	public:
		glm::vec4 Color = { 1.0f, 1.0f , 1.0f , 1.0f };

		// Thickness of the circle in range [0,1]
		float Thickness = 1.0f;

		// Circumference of the circle in range [0,1]
		float Circumference = 1.0;

		// Number of gaps in the circle
		uint32_t GapCount = 0;

		// Size of the gap in range [0,1]
		float GapSize = 0.5;

		// Rotation in range [0, 1]
		float Rotation = 0.0f;
	public:
		CircleProps& WithColor(const glm::vec4& color)
		{
			Color = color;
			return *this;
		}

		CircleProps& WithThickness(float thickness)
		{
			Thickness = thickness;
			return *this;
		}

		CircleProps& WithCircumference(float circumference)
		{
			Circumference = circumference;
			return *this;
		}

		CircleProps& WithGaps(uint32_t count, float size)
		{
			GapCount = count;
			GapSize = size;
			return *this;
		}

		CircleProps& WithRotation(float rotation)
		{
			Rotation = rotation;
			return *this;
		}
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