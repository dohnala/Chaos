#include "Map.h"

void Map::Init()
{
	m_Player.Init({ 0.0f, 0.0f });
}

void Map::OnUpdate(Chaos::Timestep ts)
{
	m_Player.OnUpdate(ts);
}

void Map::OnRender()
{
	Chaos::Renderer::DrawCircle({ -4.0f, -4.0f }, 1.0f, { 0.8f, 0.8f, 0.3f, 1.0f }, 0.5f, 0.2f);
	Chaos::Renderer::DrawCircle({  4.0f, -4.0f }, 1.0f, { 0.8f, 0.8f, 0.3f, 1.0f }, 0.5f, 0.2f);
	Chaos::Renderer::DrawCircle({  4.0f,  4.0f }, 1.0f, { 0.8f, 0.8f, 0.3f, 1.0f }, 0.5f, 0.2f);
	Chaos::Renderer::DrawCircle({ -4.0f,  4.0f }, 1.0f, { 0.8f, 0.8f, 0.3f, 1.0f }, 0.5f, 0.2f);

	m_Player.OnRender();
}