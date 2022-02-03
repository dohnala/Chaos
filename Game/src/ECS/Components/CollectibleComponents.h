#pragma once

#include "Chaos.h"

struct CollectibleComponent
{
	uint32_t Amount = 1;

	CollectibleComponent() = default;
	CollectibleComponent(const CollectibleComponent&) = default;
	CollectibleComponent(uint32_t amount)
		: Amount(amount) {}
};

// Entities with this component will attract collectibles in given radius
struct CollectiblePickupRadiusComponent
{
	float Radius = 3.0f;
	float DampMin = 0.0f;
	float DampMax = 0.75f;

	CollectiblePickupRadiusComponent() = default;
	CollectiblePickupRadiusComponent(const CollectiblePickupRadiusComponent&) = default;
	CollectiblePickupRadiusComponent(float radius, float dampMin = 0.0f, float dampMax = 0.75)
		: Radius(radius), DampMin(dampMin), DampMax(dampMax) {}
};