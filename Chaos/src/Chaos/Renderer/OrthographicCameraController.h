#pragma once

#include "Chaos/Core/Timestep.h"
#include "Chaos/Renderer/OrthographicCamera.h"
#include "Chaos/Events/ApplicationEvent.h"

namespace Chaos
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, float cameraHeight);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }
	private:
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_CameraHeight;
		glm::vec2 m_Position = {0.0f, 0.0f};

		OrthographicCamera m_Camera;
	};
}