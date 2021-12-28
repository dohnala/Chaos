#pragma once

#include "Chaos.h"

#include "Map.h"

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
	const float m_CameraHeight = 20.0f;
	const float m_CameraSpeed = 3.0f;
	const MapProps m_MapProps = { { 40.0f, 40.0f } , 20 };
private:
	Chaos::OrthographicCameraController m_CameraController;
	Map m_Map;
};