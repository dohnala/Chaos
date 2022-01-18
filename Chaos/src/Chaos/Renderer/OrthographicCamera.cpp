#include "pch.h"
#include "Chaos/Renderer/OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Chaos
{
	OrthographicCamera::OrthographicCamera()
	{
		RecalculateProjection();
	}

	void OrthographicCamera::SetProjection(float size, float zNear, float zFar)
	{
		m_Size = size;
		m_Near = zNear;
		m_Far = zFar;

		RecalculateProjection();
	}

	void OrthographicCamera::SetViewport(uint32_t width, uint32_t height)
	{
		CH_CORE_ASSERT(width > 0 && height > 0, "Viewport cannot be 0!");

		m_AspectRatio = (float)width / (float)height;

		RecalculateProjection();
	}

	void OrthographicCamera::RecalculateProjection()
	{
		float left = -m_Size * m_AspectRatio * 0.5f;
		float right = m_Size * m_AspectRatio * 0.5f;
		float bottom = -m_Size * 0.5f;
		float top = m_Size * 0.5f;

		m_Projection = glm::ortho(left, right, bottom, top, m_Near, m_Far);
	}
}