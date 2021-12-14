#pragma once

#include "Chaos/Core/Base.h"

#pragma warning(push, 0)
#include "spdlog/spdlog.h"
#pragma warning(pop)

namespace Chaos 
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetAppLogger() { return s_AppLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_AppLogger;
	};
}

#define CH_CORE_TRACE(...)    ::Chaos::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CH_CORE_INFO(...)     ::Chaos::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CH_CORE_WARN(...)     ::Chaos::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CH_CORE_ERROR(...)    ::Chaos::Log::GetCoreLogger()->error(__VA_ARGS__)

#define CH_TRACE(...)			::Chaos::Log::GetAppLogger()->trace(__VA_ARGS__)
#define CH_INFO(...)			::Chaos::Log::GetAppLogger()->info(__VA_ARGS__)
#define CH_WARN(...)			::Chaos::Log::GetAppLogger()->warn(__VA_ARGS__)
#define CH_ERROR(...)			::Chaos::Log::GetAppLogger()->error(__VA_ARGS__)
