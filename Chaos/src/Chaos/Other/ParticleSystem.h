#pragma once

#include "Chaos/Core/Base.h"
#include "Chaos/Core/Timestep.h"

#include <glm/glm.hpp>

namespace Chaos
{
	class ParticleProps
	{
	public:
		friend class ParticlePropsBuilder;
		friend class ParticleSystem;

		static ParticlePropsBuilder Create();
	private:
		ParticleProps() = default;

		float m_PositionRadiusVariance = 0.0f;
		
		glm::vec2 m_Direction = { 0.0f, 1.0f };
		float m_DirectionAngleVariance = glm::radians(90.0f);
		
		float m_Speed = 1.0f;
		float m_SpeedVariance = 0.0f;
		
		float m_Size = 1.0f;
		float m_SizeVariance = 0.0f;
		
		glm::vec4 m_ColorFrom = { 1.0f, 1.0f, 1.0f, 1.0f };
		glm::vec4 m_ColorTo = { 1.0f, 1.0f, 1.0f, 1.0f };

		float m_Alpha = 1.0f;
		float m_AlphaVariance = 0.0f;
		float m_AlphaEnd = 0.0f;
		
		float m_LifeTime = 1.0f;
		float m_LifeTimeVariance = 0.0f;
	};

	class ParticlePropsBuilder
	{
	public:
		ParticlePropsBuilder& WithPositionVariance(float radius)
		{
			m_ParticleProps.m_PositionRadiusVariance = radius;
			return *this;
		}

		ParticlePropsBuilder& WithDirection(const glm::vec2& direction)
		{
			m_ParticleProps.m_Direction = direction;
			return *this;
		}

		ParticlePropsBuilder& WithDirectionVariance(float coneAngleRad)
		{
			m_ParticleProps.m_DirectionAngleVariance = coneAngleRad;
			return *this;
		}

		ParticlePropsBuilder& WithSpeed(float speed, float speedVariance = 0.0f)
		{
			m_ParticleProps.m_Speed = speed;
			m_ParticleProps.m_SpeedVariance = speedVariance;
			return *this;
		}

		ParticlePropsBuilder& WithSize(float size, float sizeVariance = 0.0f)
		{
			m_ParticleProps.m_Size = size;
			m_ParticleProps.m_SizeVariance = sizeVariance;
			return *this;
		}

		ParticlePropsBuilder& WithColor(const glm::vec4& color)
		{
			m_ParticleProps.m_ColorFrom = color;
			m_ParticleProps.m_ColorTo = color;
			return *this;
		}

		ParticlePropsBuilder& WithColorGradient(const glm::vec4& colorFrom, const glm::vec4& colorTo)
		{
			m_ParticleProps.m_ColorFrom = colorFrom;
			m_ParticleProps.m_ColorTo = colorTo;
			return *this;
		}

		ParticlePropsBuilder& WithAlpha(float alpha, float alphaVariance, float alphaEnd)
		{
			m_ParticleProps.m_Alpha = alpha;
			m_ParticleProps.m_AlphaVariance = alphaVariance;
			m_ParticleProps.m_AlphaEnd = alphaEnd;
			return *this;
		}

		ParticlePropsBuilder& WithLifeTime(float lifeTime, float lifeTimeVariance)
		{
			m_ParticleProps.m_LifeTime = lifeTime;
			m_ParticleProps.m_LifeTimeVariance = lifeTimeVariance;
			return *this;
		}

		operator ParticleProps && ()
		{
			return std::move(m_ParticleProps);
		}
	private:
		ParticleProps m_ParticleProps;
	};

	class ParticleSystem
	{
	public:
		ParticleSystem(uint32_t maxParticles);

		void OnUpdate(Timestep ts);
		void OnRender();

		void Emit(const ParticleProps& particleProps, const glm::vec2& position, uint32_t count = 1);
		void Emit(const ParticleProps& particleProps, const glm::vec2& position, const glm::vec2& direction, uint32_t count = 1);
	private:
		struct Particle
		{
			glm::vec2 Position;
			glm::vec2 Velocity;
			float Size;
			glm::vec4 Color;
			float Alpha;
			float AlphaEnd;
			float LifeTime;
			float LifeRemaining;
			bool Active = false;
		};
	private:
		std::vector<Particle> m_ParticlePool;
		size_t m_PoolIndex;
	};
}