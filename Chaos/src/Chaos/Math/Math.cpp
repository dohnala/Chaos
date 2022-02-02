#include "pch.h"
#include "Chaos/Math/Math.h"

namespace Chaos::Math
{
	static float s_Epsilon = 0.0001f;
	static float s_Residual = 0.01f;
	// Log_e(s_Residual)
	static float s_LogResidual = -4.605170186f;

	float Damp(float value, float damp, float deltaTime)
	{
		if (damp < s_Epsilon || glm::abs(value) < s_Epsilon)
		{
			return value;
		}

		if (deltaTime < s_Epsilon)
		{
			return 0.0f;
		}

		float k = -s_LogResidual / damp;
		return value * (1.0f - glm::exp(-k * deltaTime));
	}

	glm::vec2 Damp(const glm::vec2& value, float damp, float deltaTime)
	{
		return {
			Damp(value.x, damp, deltaTime),
			Damp(value.y, damp, deltaTime)
		};
	}

	glm::vec2 PerpendicularClockwise(const glm::vec2& vec)
	{
		return { vec.y, -vec.x };
	}

	glm::vec2 PerpendicularCounterClockwise(const glm::vec2& vec)
	{
		return { -vec.y, vec.x };
	}
}