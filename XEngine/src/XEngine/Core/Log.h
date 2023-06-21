#pragma once

#include "XEngine/Core/Core.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace XEngine {

	class XENGINE_API Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		// logger for CoreEngine
		static Ref<spdlog::logger> s_CoreLogger;
		// logger for Client
		static Ref<spdlog::logger> s_ClientLogger;
	};

}

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
	return os << glm::to_string(quaternion);
}

// Core Log macros
#define XENGINE_CORE_TRACE(...)    ::XEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define XENGINE_CORE_INFO(...)     ::XEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define XENGINE_CORE_WARN(...)     ::XEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define XENGINE_CORE_ERROR(...)    ::XEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define XENGINE_CORE_CRITICAL(...) ::XEngine::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client Log macros
#define XENGINE_TRACE(...)         ::XEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define XENGINE_INFO(...)          ::XEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define XENGINE_WARN(...)          ::XEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define XENGINE_ERROR(...)         ::XEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define XENGINE_CRITICAL(...)      ::XEngine::Log::GetClientLogger()->critical(__VA_ARGS__)




