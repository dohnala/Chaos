#include "pch.h"
#include "Chaos/Renderer/OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Chaos
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, const glm::vec4& viewport)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f), m_Viewport(viewport)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { m_Position.x, m_Position.y, 0.0f });

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	glm::vec2 OrthographicCamera::ScreenToWorldPosition(const glm::vec2& screenPosition) const
	{
		auto world = glm::unProject(glm::vec3(screenPosition.x, m_Viewport.w - screenPosition.y, 0.0f), m_ViewMatrix, m_ProjectionMatrix, m_Viewport);

		return { world.x, world.y };
	}
}