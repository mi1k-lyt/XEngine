#pragma once

#include <memory>

#ifdef XENGINE_PLATFORM_WINDOWS
	#ifdef XENGINE_BUILD_DLL
		#define XENGINE_API __declspec(dllexport)
	#else 
		#define XENGINE_API __declspec(dllimport)
	#endif
#else
	#error XEngine only supports Windows now!
#endif

#ifdef XENGINE_ENABLE_ASSERTS
	#define XENGINE_ASSERT(x, ...) {if(!(x)) {XENGINE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define XENGINE_CORE_ASSERT(x, ...) {if(!(x)) {XENGINE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define XENGINE_ASSERT(x, ...)
	#define XENGINE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

namespace XEngine {

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