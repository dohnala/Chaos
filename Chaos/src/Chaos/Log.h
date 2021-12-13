#pragma once

#include <memory>

#include "spdlog/spdlog.h"

namespace Chaos 
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetAppLogger() { return s_AppLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_EngineLogger;
		static std::shared_ptr<spdlog::logger> s_AppLogger;
	};
}

#define CH_ENGINE_TRACE(...)    ::Chaos::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define CH_ENGINE_INFO(...)     ::Chaos::Log::GetEngineLogger()->info(__VA_ARGS__)
#define CH_ENGINE_WARN(...)     ::Chaos::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define CH_ENGINE_ERROR(...)    ::Chaos::Log::GetEngineLogger()->error(__VA_ARGS__)

#define CH_TRACE(...)			::Chaos::Log::GetAppLogger()->trace(__VA_ARGS__)
#define CH_INFO(...)			::Chaos::Log::GetAppLogger()->info(__VA_ARGS__)
#define CH_WARN(...)			::Chaos::Log::GetAppLogger()->warn(__VA_ARGS__)
#define CH_ERROR(...)			::Chaos::Log::GetAppLogger()->error(__VA_ARGS__)
