#include "Debug/CreatureComponentPanel.h"
#include "ECS/Components/RenderComponents.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

void CreatureComponentPanel::OnImGuiRender()
{
	auto& creature = m_SelectedEntity.GetComponent<CreatureComponent>();

	ImGui::Begin("Creature");

	ImGui::DragFloat("Radius", &creature.Radius, 0.05f, 0.0f, 10.0f);
	ImGui::Separator();
	ImGui::DragScalar("Tentacles", ImGuiDataType_::ImGuiDataType_U32, &creature.CreatureProps.TentacleCount);
	ImGui::DragFloat("Length", &creature.CreatureProps.TentacleLength, 0.05f, 0.0f, 1.0f);
	ImGui::DragFloat("Rigidity", &creature.CreatureProps.TentacleRigidity, 0.05f, 0.0f, 1.0f);
	ImGui::Separator();
	ImGui::DragFloat2("Velocity", glm::value_ptr(creature.CreatureProps.Velocity), 1.0f, -15.0f, 15.0f);
	ImGui::Separator();
	ImGui::Checkbox("Pixelation", &creature.CreatureProps.Pixelation);

	ImGui::End();
}

void CreatureComponentPanel::SetSelectedEntity(Chaos::Entity entity)
{
	m_SelectedEntity = entity;
}