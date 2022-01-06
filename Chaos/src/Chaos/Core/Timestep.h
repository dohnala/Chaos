#pragma once

namespace Chaos
{
	class Timestep
	{
	public:
		Timestep(float time, float deltaTime)
			: m_Time(time), m_DeltaTime(deltaTime)
		{}

		float GetTime() const { return m_Time; }
		float GetDeltaTime() const { return m_DeltaTime; }
	private:
		float m_Time;
		float m_DeltaTime;
	};
}