#pragma once

#include "Chaos/Core/Base.h"
#include "Chaos/Core/Timestep.h"

#include <glm/glm.hpp>

namespace Chaos
{
	struct ParticleProps
	{
		glm::vec2 Position = { 0.0f, 0.0f };
		float PositionRadiusVariance = 0.0f;
		
		glm::vec2 Direction = { 0.0f, 1.0f };
		float DirectionAngleVariance = glm::radians(90.0f);
		
		float Speed = 1.0f;
		float SpeedVariance = 0.0f;
		
		float Size = 1.0f;
		float SizeVariance = 0.0f;
		
		glm::vec4 ColorFrom = { 1.0f, 1.0f, 1.0f, 1.0f };
		glm::vec4 ColorTo = { 1.0f, 1.0f, 1.0f, 1.0f };

		float Alpha = 1.0f;
		float AlphaVariance = 0.0f;
		float AlphaEnd = 0.0f;
		
		float LifeTime = 1.0f;
		float LifeTimeVariance = 0.0f;
	};

	class ParticleSystem
	{
	public:
		ParticleSystem(uint32_t maxParticles);

		void OnUpdate(Timestep ts);
		void OnRender();

		void Emit(const ParticleProps& particleProps, uint32_t count = 1);
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