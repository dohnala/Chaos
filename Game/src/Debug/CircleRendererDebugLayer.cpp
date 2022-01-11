#include "CircleRendererDebugLayer.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

CircleRendererDebugLayer::CircleRendererDebugLayer()
	: Layer("CircleRendererDebugLayer"), m_CameraController(Chaos::Application::Get().GetWindow().GetAspectRatio(), m_CameraHeight, 0.0f)
{}

void CircleRendererDebugLayer::OnAttach()
{
	
}

void CircleRendererDebugLayer::OnDetach()
{
	
}

void CircleRendererDebugLayer::OnUpdate(Chaos::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	Chaos::Renderer::SetClearColor(Color::DarkGrey);
	Chaos::Renderer::Clear();

	Chaos::Renderer::BeginScene(m_CameraController.GetCamera(), ts);
	Chaos::Renderer::DrawCircle({ 0.0f, 0.0f }, m_Radius, m_CircleProps);
	Chaos::Renderer::EndScene();
}

void CircleRendererDebugLayer::OnImGuiRender()
{
	ImGui::Begin("Circle Renderer");

	ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float | ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_PickerHueWheel);

	if (ImGui::CollapsingHeader("Shape", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("Radius", &m_Radius, 0.05f, 0.0f, 10.0f);
		ImGui::DragFloat("Border Noise", &m_CircleProps.BorderDistortion, 0.05f, 0.05f, 1.0f);
		ImGui::DragFloat("Direction Noise", &m_CircleProps.DirectionDistortion, 0.1f, 0.00f, 5.0f);
	}

	if (ImGui::CollapsingHeader("Color", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::ColorEdit4("Color Inside", glm::value_ptr(m_CircleProps.ColorInside));
		ImGui::ColorEdit4("Color Outside", glm::value_ptr(m_CircleProps.ColorOutside));
		ImGui::DragFloat("Color Ratio", &m_CircleProps.ColorRatio, 0.1f, 0.0f, 3.0f);
	}

	if (ImGui::CollapsingHeader("Misc", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat2("Direction", glm::value_ptr(m_CircleProps.Direction), 1.0f, -1.0f, 1.0f);
	}
	
	ImGui::End();
}

void CircleRendererDebugLayer::OnEvent(Chaos::Event& event)
{
	m_CameraController.OnEvent(event);
}