#pragma once

#include <glm/glm.hpp>

namespace Chaos
{
	class Entity
	{
	public:
		const glm::vec2& GetPosition() const { return m_Position; };
		void SetPosition(const glm::vec2& position) { m_Position = position; }
	protected:
		glm::vec2 m_Position;
	};
}