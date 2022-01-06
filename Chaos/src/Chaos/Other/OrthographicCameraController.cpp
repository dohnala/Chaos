#include "pch.h"
#include "Chaos/Other/OrthographicCameraController.h"
#include "Chaos/Core/Application.h"

namespace Chaos
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, float cameraHeight, float cameraSpeed)
		: m_AspectRatio(aspectRatio), m_CameraHeight(cameraHeight), m_CameraSpeed(cameraSpeed), m_Camera(
			-m_CameraHeight * m_AspectRatio * 0.5f,
			m_CameraHeight * m_AspectRatio * 0.5f,
			-m_CameraHeight * 0.5f,
			m_CameraHeight * 0.5f)
	{}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		if (m_EntityToFollow)
		{
			glm::vec2 target = m_Position;

			if (m_Bounds.Max - m_Bounds.Min == glm::vec2(0.0f))
			{
				target = m_EntityToFollow->GetPosition();
			}
			else
			{
				target = glm::clamp(m_EntityToFollow->GetPosition(), 
					m_Bounds.Min + glm::vec2(m_CameraHeight * m_AspectRatio * 0.5f, m_CameraHeight * 0.5f),
					m_Bounds.Max - glm::vec2(m_CameraHeight * m_AspectRatio * 0.5f, m_CameraHeight * 0.5f));
			}

			m_Position = glm::mix(m_Position, target, m_CameraSpeed * ts.GetDeltaTime());
			m_Camera.SetPosition(m_Position);
		}
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(CH_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	void OrthographicCameraController::StartFollow(const Entity* entity)
	{
		m_EntityToFollow = entity;
	}

	void OrthographicCameraController::StopFollow()
	{
		m_EntityToFollow = nullptr;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(
			-m_CameraHeight * m_AspectRatio * 0.5f,
			m_CameraHeight * m_AspectRatio * 0.5f,
			-m_CameraHeight * 0.5f,
			m_CameraHeight * 0.5f);

		return false;
	}
}