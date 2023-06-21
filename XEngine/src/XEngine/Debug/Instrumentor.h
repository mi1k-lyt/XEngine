#pragma once
#include "XEngine/Core/Log.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>
#include <mutex>
#include <sstream>

#define XENGINE_PROFILE 0
#if XENGINE_PROFILE
// Resolve which function signature macro will be used. Note that this only
// is resolved when the (pre)compiler starts, so the syntax highlighting
// could mark the wrong one in your editor!
#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
#define XENGINE_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
#define XENGINE_FUNC_SIG __PRETTY_FUNCTION__
#elif (defined(__FUNCSIG__) || (_MSC_VER))
#define XENGINE_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
#define XENGINE_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
#define XENGINE_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#define XENGINE_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
#define XENGINE_FUNC_SIG __func__
#else
#define XENGINE_FUNC_SIG "XENGINE_FUNC_SIG unknown!"
#endif

#define XENGINE_PROFILE_BEGIN_SESSION(name, filepath) ::XEngine::Instrumentor::Get().BeginSession(name, filepath)
#define XENGINE_PROFILE_END_SESSION() ::XEngine::Instrumentor::Get().EndSession()
#define XENGINE_PROFILE_SCOPE_LINE2(name, line) constexpr auto fixedName##line = ::XEngine::InstrumentorUtils::CleanupOutputString(name, "__cdecl ");\
											   ::XEngine::InstrumentationTimer timer##line(fixedName##line.Data)
#define XENGINE_PROFILE_SCOPE_LINE(name, line) XENGINE_PROFILE_SCOPE_LINE2(name, line)
#define XENGINE_PROFILE_SCOPE(name) XENGINE_PROFILE_SCOPE_LINE(name, __LINE__)
#define XENGINE_PROFILE_FUNCTION() XENGINE_PROFILE_SCOPE(XENGINE_FUNC_SIG) 
#else
#define XENGINE_PROFILE_BEGIN_SESSION(name, filepath)
#define XENGINE_PROFILE_END_SESSION()
#define XENGINE_PROFILE_SCOPE(name)
#define XENGINE_PROFILE_FUNCTION()
#endif