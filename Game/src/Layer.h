#pragma once

#include "Chaos.h"

using LayerMask = uint32_t;

namespace Layer
{
	enum : LayerMask
	{
		None			=  0,
		Everything		= ~0u,
		World			=  1,
		Player			=  2,
		Enemy			=  4,
		Collectible		=  8,
		Projectile		= 16
	};
}