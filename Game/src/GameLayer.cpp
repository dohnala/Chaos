#include "GameLayer.h"

#include <glm/glm.hpp>

GameLayer::GameLayer()
	: Layer("GameLayer")
{
	auto& window = Chaos::Application::Get().GetWindow();
	CreateCamera(window.GetWidth(), window.GetHeight());
}

void GameLayer::OnAttach()
{
	m_Map.Init();
}

void GameLayer::OnUpdate(Chaos::Timestep ts)
{
	m_Map.OnUpdate(ts);

	Chaos::Renderer::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Chaos::Renderer::Clear();

	Chaos::Renderer::BeginScene(*m_Camera);
	m_Map.OnRender();
	Chaos::Renderer::EndScene();
}

void GameLayer::OnEvent(Chaos::Event& event)
{
	Chaos::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Chaos::WindowResizeEvent>(CH_BIND_EVENT_FN(GameLayer::OnWindowResize));
}

bool GameLayer::OnWindowResize(Chaos::WindowResizeEvent& event)
{
	float aspectRation = (float)event.GetWidth() / (float)event.GetHeight();

	m_Camera->SetProjection(-m_CameraHeight * aspectRation, m_CameraHeight * aspectRation, -m_CameraHeight, m_CameraHeight);

	return false;
}

void GameLayer::CreateCamera(uint32_t width, uint32_t height)
{
	float aspectRation = (float)width / (float)height;

	m_Camera = Chaos::CreateScope<Chaos::OrthographicCamera>(-m_CameraHeight * aspectRation, m_CameraHeight * aspectRation, -m_CameraHeight, m_CameraHeight);
}