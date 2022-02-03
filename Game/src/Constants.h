#pragma once

#include <glm/glm.hpp>

namespace Color
{
	static glm::vec4 White		= { 1.000f, 1.000f, 1.000f, 1.0f };
	static glm::vec4 Black		= { 0.000f, 0.000f, 0.000f, 1.0f };
	static glm::vec4 Grey		= { 0.250f, 0.250f, 0.250f, 1.0f };
	static glm::vec4 DarkGrey	= { 0.100f, 0.100f, 0.100f, 1.0f };

	static glm::vec4 Yellow		= { 1.000f, 0.776f, 0.200f, 1.0f };		// H=0.120, S=0.8, V=1.0 
	static glm::vec4 Red		= { 1.000f, 0.186f, 0.186f, 1.0f };		// H=1.000, S=0.8, V=1.0 
	static glm::vec4 Blue		= { 0.200f, 1.000f, 1.000f, 1.0f };		// H=0.500, S=0.8, V=1.0 
	static glm::vec4 Green		= { 0.600f, 1.000f, 0.200f, 1.0f };		// H=0.250, S=0.8, V=1.0 
	static glm::vec4 Pink		= { 1.000f, 0.200f, 0.679f, 1.0f };		// H=0.900, S=0.8, V=1.0 

	static glm::vec4 WithAlpha(const glm::vec4& color, float alpha)
	{
		return { color.r, color.g, color.b,alpha };
	}
}

using LayerMask = uint32_t;

namespace Layer
{
	enum : LayerMask
	{
		None = 0,
		Everything = ~0u,
		World = 1,
		Player = 2,
		Enemy = 4,
		Collectible = 8,
		Projectile = 16
	};
}

enum class SkillID
{
	Fireball = 0,
	PoisonBolt,
	ArcaneShot
};