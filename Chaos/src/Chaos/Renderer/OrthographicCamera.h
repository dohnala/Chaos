#pragma once

#include "Chaos/Core/Base.h"
#include "Chaos/Renderer/Camera.h"

#include <glm/glm.hpp>

namespace Chaos
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera();
		virtual ~OrthographicCamera() = default;

		void SetProjection(float size, float zNear = -1.0f, float zFar = 1.0f);
		void SetViewport(uint32_t width, uint32_t height);

		float GetOrthographicSize() const { return m_Size; }
		void SetOrthographicSize(float size) { m_Size = size; RecalculateProjection(); }

		float GetAspectRatio() const { return m_AspectRatio; }
		
	private:
		void RecalculateProjection();
	private:
		float m_Size = 10.0f;
		float m_Near = -1.0f;
		float m_Far = 1.0f;
		float m_AspectRatio = 0.0f;
	};
}