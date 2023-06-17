#pragma once

#ifdef XE_PLATFORM_WINDOWS
	#ifdef XE_BUILD_DLL
		#define XE_API __declspec(dllexport)
	#else 
		#define XE_API __declspec(dllimport)
	#endif
#else
	#error XEngine only supports Windows now!
#endif