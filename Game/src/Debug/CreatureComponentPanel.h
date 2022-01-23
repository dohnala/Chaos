#pragma once

#include "Chaos.h"

class CreatureComponentPanel
{
public:
	CreatureComponentPanel() = default;

	void OnImGuiRender();

	Chaos::Entity GetSelectedEntity() const { return m_SelectedEntity; }
	void SetSelectedEntity(Chaos::Entity entity);
private:
	Chaos::Entity m_SelectedEntity;
};