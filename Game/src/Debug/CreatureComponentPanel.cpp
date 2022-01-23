#include "Debug/CreatureComponentPanel.h"
#include "ECS/Components/RenderComponents.h"

#include <imgui/imgui.h>

void CreatureComponentPanel::OnImGuiRender()
{
	auto& creature = m_SelectedEntity.GetComponent<CreatureComponent>();

	ImGui::Begin("Creature");

	ImGui::DragFloat("Radius", &creature.Radius, 0.05f, 0.0f, 10.0f);
	ImGui::Checkbox("Antialiasing", &creature.CreatureProps.Antialiasing);
	ImGui::Checkbox("Pixelation", &creature.CreatureProps.Pixelation);

	ImGui::End();
}

void CreatureComponentPanel::SetSelectedEntity(Chaos::Entity entity)
{
	m_SelectedEntity = entity;
}