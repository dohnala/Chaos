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

	class CreatureProps
	{
	public:
		friend class CreaturePropsBuilder;

		static CreaturePropsBuilder Create();
	public:
		// Number of tentacles
		uint32_t TentacleCount = 0;

		// Length of the tentacle compared to its body in [0, 1] range
		float TentacleLength = 0.0f;

		// Rigidity of the tentacle
		// 0 - no rigid at all
		// 1 - very rigid
		float TentacleRigidity = 0.25f;

		glm::vec2 Velocity = { 0.0f, 0.0f };
	private:
		CreatureProps() = default;
	};

	class CreaturePropsBuilder
	{
	public:
		CreaturePropsBuilder& WithTentacles(uint32_t count, float length, float rigidity = 0.25f)
		{
			m_CreatureProps.TentacleCount = count;
			m_CreatureProps.TentacleLength = length;
			m_CreatureProps.TentacleRigidity = rigidity;
			return *this;
		}

		operator CreatureProps && ()
		{
			return std::move(m_CreatureProps);
		}
	private:
		CreatureProps m_CreatureProps;
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
		static void DrawCreature(const glm::vec2& position, float radius, const CreatureProps& creatureProps);

		static GraphicsAPI::API GetAPI() { return s_GraphicsAPI->GetAPI(); }
	private:
	private:
		static Scope<GraphicsAPI> s_GraphicsAPI;
	};
}