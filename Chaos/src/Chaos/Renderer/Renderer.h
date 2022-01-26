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
		// Controls the color gradient
		glm::vec4 ColorInside = { 1.0f, 1.0f , 1.0f , 1.0f };
		glm::vec4 ColorOutside = { 1.0f, 1.0f , 1.0f , 1.0f };

		// Controls the gradient between inside and outside color
		// 0 - 100% outside color
		// 1 - 50% inside color and 50% outside color
		// 3 and more - 100% inside color
		float ColorRatio = 1.0f;

		// Controls how much distortion is across the border
		// 0 - no distortion
		// 1 - full distortion
		float BorderDistortion = 0.0f;

		// Direction of the circle used to animate shape and color
		glm::vec2 Direction = { 0.0f, 0.0f };

		// Controls how much is the circle distorted based on the direction
		// 0 - no distortion
		// N - bigger distortion
		float DirectionDistortion = 0.0f;
	private:
		CircleProps() = default;
	};

	class CirclePropsBuilder
	{
	public:
		CirclePropsBuilder& WithColor(const glm::vec4& color)
		{
			m_CircleProps.ColorInside = color;
			m_CircleProps.ColorOutside = color;
			m_CircleProps.ColorRatio = 1.0f;
			return *this;
		}

		CirclePropsBuilder& WithColorGradient(const glm::vec4& colorInside, const glm::vec4& colorOutside, float ratio = 1.0f)
		{
			m_CircleProps.ColorInside = colorInside;
			m_CircleProps.ColorOutside = colorOutside;
			m_CircleProps.ColorRatio = ratio;
			return *this;
		}

		CirclePropsBuilder& WithBorderDistortion(float borderDistortion)
		{
			m_CircleProps.BorderDistortion = borderDistortion;
			return *this;
		}

		CirclePropsBuilder& WithDirectionDistortion(float directionDistortion)
		{
			m_CircleProps.DirectionDistortion = directionDistortion;
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

		// TODO: should be hardcoded in shader
		bool Pixelation = false;
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

		CreaturePropsBuilder& WithPixelation(bool pixelation)
		{
			m_CreatureProps.Pixelation = pixelation;
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