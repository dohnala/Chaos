#pragma once

#include "Chaos.h"
#include "Color.h"

#include <glm/glm.hpp>

class CircleRendererDebugLayer : public Chaos::Layer
{
public:
	CircleRendererDebugLayer();
	virtual ~CircleRendererDebugLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Chaos::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Chaos::Event& event) override;
private:
	const float m_CameraHeight = 30.0f;
private:
	Chaos::OrthographicCameraController m_CameraController;
	float m_Radius = 1.0f;
	Chaos::CircleProps m_CircleProps = Chaos::CircleProps::Create();
};