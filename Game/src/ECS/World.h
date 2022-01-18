#pragma once

#include "Chaos.h"

#include <glm/glm.hpp>

class World : public Chaos::World
{
public:
	World(glm::vec2 size);
	virtual ~World() = default;

	const Chaos::Bounds& GetBounds() const { return m_Bounds; }

	glm::vec2 GetRandomLocation() const;
	Chaos::ParticleSystem& GetParticleSystem() { return m_ParticleSystem; }

	virtual void OnUpdate(Chaos::Timestep ts) override;
	virtual void OnViewportResize(uint32_t width, uint32_t height) override;
private:
	glm::vec2 m_Size;
	Chaos::Bounds m_Bounds;
	Chaos::Entity m_Camera;
	Chaos::Entity m_Player;

	Chaos::ParticleSystem m_ParticleSystem = Chaos::ParticleSystem(500);
};