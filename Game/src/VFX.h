#pragma once

#include "Chaos.h"

namespace VFX
{
	struct BurstEffect
	{
	public:
		uint32_t ParticleCount = 0;

		Chaos::ParticleProps ParticleProps = Chaos::ParticleProps::Create();
	public:
		static BurstEffect Create()
		{
			return BurstEffect();
		}
	public:
		BurstEffect& WithParticle(const Chaos::ParticleProps& particleProps)
		{
			ParticleProps = particleProps;
			return *this;
		}

		BurstEffect& WithParticleCount(uint32_t particleCount)
		{
			ParticleCount = particleCount;
			return *this;
		}
	};

	struct TrailEffect
	{
	public:
		enum class DirectionType
		{
			Forward = 0,
			Sin,
			Cos
		};
	public:
		float ParticleCountPerUnit = 0.0f;

		Chaos::ParticleProps ParticleProps = Chaos::ParticleProps::Create();

		DirectionType Direction = DirectionType::Forward;
	public:
		static TrailEffect Create()
		{
			return TrailEffect();
		}
	public:
		TrailEffect& WithParticle(const Chaos::ParticleProps& particleProps)
		{
			ParticleProps = particleProps;
			return *this;
		}

		TrailEffect& WithParticleCountPerUnit(float particleCountPerUnit)
		{
			ParticleCountPerUnit = particleCountPerUnit;
			return *this;
		}

		TrailEffect& WithDirectionType(TrailEffect::DirectionType direction)
		{
			Direction = direction;
			return *this;
		}
	};
}