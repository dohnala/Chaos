#include "GameLayer.h"
#include "Color.h"

GameLayer::GameLayer()
	: Layer("GameLayer"), m_CameraController(Chaos::Application::Get().GetWindow().GetAspectRatio(), m_CameraHeight)
{}

void GameLayer::OnAttach()
{
	m_Map.Init(m_MapProps);

	m_CameraController.SetBounds(m_Map.GetBounds());
	m_CameraController.StartFollow(&m_Map.GetPlayer());
}

void GameLayer::OnDetach()
{
	m_CameraController.StopFollow();
}

void GameLayer::OnUpdate(Chaos::Timestep ts)
{
	m_Map.OnUpdate(ts);
	m_CameraController.OnUpdate(ts);

	Chaos::Renderer::SetClearColor(Color::DarkGrey);
	Chaos::Renderer::Clear();

	Chaos::Renderer::BeginScene(m_CameraController.GetCamera());
	m_Map.OnRender();
	Chaos::Renderer::EndScene();
}

void GameLayer::OnEvent(Chaos::Event& event)
{
	m_CameraController.OnEvent(event);
}