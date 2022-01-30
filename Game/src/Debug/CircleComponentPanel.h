#pragma once

#include "Chaos.h"

class CircleComponentPanel
{
public:
	CircleComponentPanel() = default;

	void OnImGuiRender();

	Chaos::Entity GetSelectedEntity() const { return m_SelectedEntity; }
	void SetSelectedEntity(Chaos::Entity entity);
private:
	Chaos::Entity m_SelectedEntity;
};