#pragma once

#include "core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace XEngine {

	class XE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClinetLogger; }

	private:
		// logger for CoreEngine
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		// logger for Client
		static std::shared_ptr<spdlog::logger> s_ClinetLogger;
	};

}

// Core Log macros
#define XE_CORE_TRACE(...)   ::XEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define XE_CORE_INFO(...)    ::XEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define XE_CORE_WARN(...)    ::XEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define XE_CORE_ERROR(...)   ::XEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define XE_CORE_FATAL(...)   ::XEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client Log macros
#define XE_TRACE(...)        ::XEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define XE_INFO(...)         ::XEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define XE_WARN(...)         ::XEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define XE_ERROR(...)        ::XEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define XE_FATAL(...)        ::XEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)




