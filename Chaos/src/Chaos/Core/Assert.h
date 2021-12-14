#pragma once

#include "Chaos/Core/Base.h"

#ifdef CH_ENABLE_ASSERTS
	#define CH_CORE_ASSERT(x, ...) { if(!(x)) { CH_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define CH_ASSERT(x, ...) { if(!(x)) { CH_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define CH_CORE_ASSERT(x, ...)
	#define CH_ASSERT(x, ...)
#endif