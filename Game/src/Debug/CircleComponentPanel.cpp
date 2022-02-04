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
		ImGui::DragFloat("Thickness", &circle.CircleProps.Thickness, 0.01f, 0.0f, 1.0f);
		ImGui::DragFloat("Circumference", &circle.CircleProps.Circumference, 0.01f, 0.0f, 1.0f);
		ImGui::DragScalar("Gap count", ImGuiDataType_::ImGuiDataType_U32, &circle.CircleProps.GapCount);
		ImGui::DragFloat("Gap size", &circle.CircleProps.GapSize, 0.01f, 0.0f, 1.0f);
		ImGui::DragFloat("Rotation", &circle.CircleProps.Rotation, 0.01f, 0.0f, 1.0f);
		
		ImGui::End();
	}
}

void CircleComponentPanel::SetSelectedEntity(Chaos::Entity entity)
{
	m_SelectedEntity = entity;
}