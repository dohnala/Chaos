#pragma once

#include <memory>

#include "Chaos/Core/PlatformDetection.h"

#ifdef CH_DEBUG
	#define CH_ENABLE_ASSERTS
#endif

#define BIT(x) (1 << x)

#define CH_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

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