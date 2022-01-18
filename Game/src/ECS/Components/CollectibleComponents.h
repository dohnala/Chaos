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