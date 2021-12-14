#pragma once

#include <memory>

#include "Chaos/Core/PlatformDetection.h"

#ifdef CH_DEBUG
	#define CH_ENABLE_ASSERTS
#endif

namespace Chaos
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

#include "Chaos/Core/Log.h"
#include "Chaos/Core/Assert.h"