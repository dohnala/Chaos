#include "pch.h"
#include "Chaos/Other/ParticleSystem.h"
#include "Chaos/Renderer/Renderer.h"
#include "Chaos/Core/Random.h"

#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtc/random.hpp>

namespace Chaos
{
	ParticlePropsBuilder ParticleProps::Create()
	{
		return ParticlePropsBuilder();
	}

	ParticleSystem::ParticleSystem(uint32_t maxParticles)
		: m_PoolIndex(maxParticles - 1)
	{
		m_ParticlePool.resize(maxParticles);
	}

	void ParticleSystem::OnUpdate(Timestep ts)
	{
		for (auto& particle : m_ParticlePool)
		{
			if (!particle.Active)
				continue;

			if (particle.LifeRemaining <= 0.0f)
			{
				particle.Active = false;
				continue;
			}

			particle.Position += particle.Velocity * ts.GetDeltaTime();
			particle.LifeRemaining -= ts.GetDeltaTime();
		}
	}

	void ParticleSystem::OnRender()
	{
		for (auto& particle : m_ParticlePool)
		{
			if (!particle.Active)
				continue;

			float life = particle.LifeRemaining / particle.LifeTime;
			float alpha = glm::lerp(particle.AlphaEnd, particle.Alpha, life);

			Renderer::DrawRect(particle.Position, { particle.Size, particle.Size }, { particle.Color.r, particle.Color.g, particle.Color.b, alpha });
		}
	}

	void ParticleSystem::Emit(const ParticleProps& particleProps, const glm::vec2& position, uint32_t count)
	{
		Emit(particleProps, position, particleProps.m_Direction, count);
	}

	void ParticleSystem::Emit(const ParticleProps& particleProps, const glm::vec2& position, const glm::vec2& direction, uint32_t count)
	{
		for (uint32_t i = 0; i < count; i++)
		{
			Particle& particle = m_ParticlePool[m_PoolIndex];

			particle.Active = true;

			particle.Position = position;
			particle.Position += particleProps.m_PositionRadiusVariance > 0.0f ? glm::circularRand(particleProps.m_PositionRadiusVariance) : glm::vec2(0.0f);

			float angle = (Random::Float() - 0.5f) * particleProps.m_DirectionAngleVariance;
			float speed = particleProps.m_Speed + (Random::Float() - 0.5f) * particleProps.m_SpeedVariance;
			particle.Velocity = glm::rotate(direction, angle) * speed;

			particle.Size = particleProps.m_Size + (Random::Float() - 0.5f) * particleProps.m_SizeVariance;

			particle.Color = glm::lerp(particleProps.m_ColorFrom, particleProps.m_ColorTo, Random::Float());
			particle.Alpha = glm::clamp(particleProps.m_Alpha + (Random::Float() - 0.5f) * particleProps.m_AlphaVariance, 0.0f, 1.0f);
			particle.AlphaEnd = particleProps.m_AlphaEnd;

			particle.LifeTime = glm::max(particleProps.m_LifeTime + (Random::Float() - 0.5f) * particleProps.m_LifeTimeVariance, 0.0f);
			particle.LifeRemaining = particleProps.m_LifeTime;

			m_PoolIndex = ((m_PoolIndex - 1) + m_ParticlePool.size()) % m_ParticlePool.size();
		}
	}
}