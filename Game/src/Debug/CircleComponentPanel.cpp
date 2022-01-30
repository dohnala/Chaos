#include "Debug/CircleComponentPanel.h"
#include "ECS/Components/RenderComponents.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

void CircleComponentPanel::OnImGuiRender()
{
	if (m_SelectedEntity.HasComponent<CircleComponent>())
	{
		auto& circle = m_SelectedEntity.GetComponent<CircleComponent>();

		ImGui::Begin("Circle");

		ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float | ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_PickerHueWheel);

		ImGui::DragFloat("Radius", &circle.Radius, 0.05f, 0.0f, 10.0f);
		ImGui::ColorEdit4("Color", glm::value_ptr(circle.CircleProps.Color));
		
		ImGui::End();
	}
}

void CircleComponentPanel::SetSelectedEntity(Chaos::Entity entity)
{
	m_SelectedEntity = entity;
}