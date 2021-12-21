#pragma once

#include "Chaos.h"

class GameLayer : public Chaos::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnUpdate(Chaos::Timestep ts) override;
	virtual void OnEvent(Chaos::Event& event) override;
private:
	bool OnWindowResize(Chaos::WindowResizeEvent& event);

	void CreateCamera(uint32_t width, uint32_t height);
private:
	const float m_CameraHeight = 10.0f;
	Chaos::Scope<Chaos::OrthographicCamera> m_Camera;
};