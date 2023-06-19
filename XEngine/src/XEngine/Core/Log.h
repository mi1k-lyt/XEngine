#pragma once

#include "XEngine/Core/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace XEngine {

	class XENGINE_API Log
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
#define XENGINE_CORE_TRACE(...)   ::XEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define XENGINE_CORE_INFO(...)    ::XEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define XENGINE_CORE_WARN(...)    ::XEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define XENGINE_CORE_ERROR(...)   ::XEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define XENGINE_CORE_FATAL(...)   ::XEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client Log macros
#define XENGINE_TRACE(...)        ::XEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define XENGINE_INFO(...)         ::XEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define XENGINE_WARN(...)         ::XEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define XENGINE_ERROR(...)        ::XEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define XENGINE_FATAL(...)        ::XEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)




