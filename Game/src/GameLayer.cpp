#include "GameLayer.h"

GameLayer::GameLayer()
	: Layer("GameLayer")
{
}

void GameLayer::OnAttach()
{
	m_World.OnViewportResize(
		Chaos::Application::Get().GetWindow().GetWidth(), 
		Chaos::Application::Get().GetWindow().GetHeight());

	m_CircleComponentPanel.SetSelectedEntity(m_World.GetPlayer());
	m_CreatureComponentPanel.SetSelectedEntity(m_World.GetPlayer());
}

void GameLayer::OnDetach()
{
	
}

void GameLayer::OnUpdate(Chaos::Timestep ts)
{
	m_World.OnUpdate(ts);
}

void GameLayer::OnImGuiRender()
{
	m_CircleComponentPanel.OnImGuiRender();
	m_CreatureComponentPanel.OnImGuiRender();
}

void GameLayer::OnEvent(Chaos::Event& event)
{
	Chaos::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Chaos::WindowResizeEvent>(CH_BIND_EVENT_FN(GameLayer::OnWindowResized));
}

bool GameLayer::OnWindowResized(Chaos::WindowResizeEvent& event)
{
	m_World.OnViewportResize(event.GetWidth(), event.GetHeight());
	return false;
}