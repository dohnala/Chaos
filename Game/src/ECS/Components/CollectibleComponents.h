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

// Collectibles within given radius will follow entity with given damp base on the distance
struct CollectibleFollowComponent
{
	float Radius = 5.0f;
	float DampMin = 0.25f;
	float DampMax = 1.0f;

	CollectibleFollowComponent() = default;
	CollectibleFollowComponent(const CollectibleFollowComponent&) = default;
	CollectibleFollowComponent(float radius, float dampMin, float dampMax)
		: Radius(radius), DampMin(dampMin), DampMax(dampMax) {}
};