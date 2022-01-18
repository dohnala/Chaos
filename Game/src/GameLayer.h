#pragma once

#include "Chaos.h"

#include "ECS/World.h"

class GameLayer : public Chaos::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Chaos::Timestep ts) override;
	virtual void OnEvent(Chaos::Event& event) override;
private:
	bool OnWindowResized(Chaos::WindowResizeEvent& event);
private:
	World m_World = World({ 60.0f, 60.0f });
};