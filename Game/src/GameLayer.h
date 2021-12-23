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
	const float m_CameraHeight = 20.0f;
	Chaos::OrthographicCameraController m_CameraController;
	
	const MapProps m_MapProps = { { 40.0f, 40.0f } , 20 };
	Map m_Map;
};