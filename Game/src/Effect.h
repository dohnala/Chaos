#pragma once

#include "Chaos.h"

namespace Effect
{
	class TrailEffect
	{
	public:
		enum class DirectionType
		{
			Forward = 0,
			Sin,
			Cos
		};

		friend class TrailEffectBuilder;

		static TrailEffectBuilder Create();
	public:

		float ParticleCountPerUnit = 1.0f;

		Chaos::ParticleProps ParticleProps = Chaos::ParticleProps::Create();

		DirectionType Direction = DirectionType::Forward;
	private:
		TrailEffect() = default;
	};

	class TrailEffectBuilder
	{
	public:
		TrailEffectBuilder& WithParticle(const Chaos::ParticleProps& particleProps)
		{
			m_TrailEffect.ParticleProps = particleProps;
			return *this;
		}

		TrailEffectBuilder& WithParticleCount(float particleCountPerUnit)
		{
			m_TrailEffect.ParticleCountPerUnit = particleCountPerUnit;
			return *this;
		}

		TrailEffectBuilder& WithDirectionType(TrailEffect::DirectionType direction)
		{
			m_TrailEffect.Direction = direction;
			return *this;
		}

		operator TrailEffect && ()
		{
			return std::move(m_TrailEffect);
		}
	private:
		TrailEffect m_TrailEffect;
	};
}