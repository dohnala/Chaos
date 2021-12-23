#pragma once

#include "Chaos.h"

#include "Map.h"

class GameLayer : public Chaos::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;

	virtual void OnUpdate(Chaos::Timestep ts) override;
	virtual void OnEvent(Chaos::Event& event) override;
private:
	bool OnWindowResize(Chaos::WindowResizeEvent& event);

	void CreateCamera(uint32_t width, uint32_t height);
private:
	const MapProps m_MapProps = { { 40.0f, 40.0f } , 20 };
	const float m_CameraHeight = 20.0f;
	Chaos::Scope<Chaos::OrthographicCamera> m_Camera;
	Map m_Map;
};