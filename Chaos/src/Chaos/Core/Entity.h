#pragma once

#include "Chaos/Core/Base.h"
#include "Chaos/Core/Timestep.h"
#include "Chaos/Events/Event.h"

#include <glm/glm.hpp>

namespace Chaos
{
	class Entity
	{
	public:
		virtual void OnUpdate(Timestep ts) {};
		virtual void OnRender() const {}

		const glm::vec2& GetPosition() const { return m_Position; };
		void SetPosition(const glm::vec2& position) { m_Position = position; }
	protected:
		glm::vec2 m_Position;
	};
}