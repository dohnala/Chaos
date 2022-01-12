#pragma once

#include "Chaos/Core/Timestep.h"
#include "Chaos/Core/Entity.h"
#include "Chaos/Renderer/OrthographicCamera.h"
#include "Chaos/Events/ApplicationEvent.h"

namespace Chaos
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(const glm::vec2& screenSize, float cameraHeight, float cameraSpeed);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void SetBounds(const Bounds bounds) { m_Bounds = bounds; };

		void StartFollow(const Entity* entity);
		void StopFollow();

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }
	private:
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_CameraHeight;
		float m_CameraSpeed;

		glm::vec2 m_Position = {0.0f, 0.0f};
		Bounds m_Bounds;

		const Entity* m_EntityToFollow = nullptr;

		OrthographicCamera m_Camera;
	};
}