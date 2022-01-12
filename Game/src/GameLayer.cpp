#include "GameLayer.h"
#include "Color.h"

static Chaos::OrthographicCamera* s_MainCamera;

glm::vec2 Chaos::Input::GetMouseWorldPosition()
{
	auto mouse = Chaos::Input::GetMousePosition();

	if (s_MainCamera)
	{
		return s_MainCamera->ScreenToWorldPosition(mouse);
	}

	return mouse;
}

GameLayer::GameLayer()
	: Layer("GameLayer"), m_CameraController(Chaos::Application::Get().GetWindow().GetSize(), m_CameraHeight, m_CameraSpeed)
{}

void GameLayer::OnAttach()
{
	m_Map.Init(m_MapProps);

	m_CameraController.SetBounds(m_Map.GetBounds());
	m_CameraController.StartFollow(&m_Map.GetPlayer());

	s_MainCamera = &m_CameraController.GetCamera();
}

void GameLayer::OnDetach()
{
	m_CameraController.StopFollow();
	s_MainCamera = nullptr;
}

void GameLayer::OnUpdate(Chaos::Timestep ts)
{
	m_Map.OnUpdate(ts);
	m_CameraController.OnUpdate(ts);

	Chaos::Renderer::SetClearColor(Color::DarkGrey);
	Chaos::Renderer::Clear();

	Chaos::Renderer::BeginScene(m_CameraController.GetCamera(), ts);
	m_Map.OnRender();
	Chaos::Renderer::EndScene();
}

void GameLayer::OnEvent(Chaos::Event& event)
{
	m_CameraController.OnEvent(event);
}