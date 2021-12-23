#include "pch.h"
#include "Chaos/Renderer/OrthographicCameraController.h"
#include "Chaos/Core/Application.h"

namespace Chaos
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, float cameraHeight)
		: m_AspectRatio(aspectRatio), m_CameraHeight(cameraHeight), m_Camera(
			-m_CameraHeight * m_AspectRatio * 0.5f,
			m_CameraHeight* m_AspectRatio * 0.5f,
			-m_CameraHeight * 0.5f,
			m_CameraHeight * 0.5f)
	{}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(CH_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
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