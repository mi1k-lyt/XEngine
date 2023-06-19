#pragma once

#ifdef XENGINE_PLATFORM_WINDOWS
	#ifdef XENGINE_BUILD_DLL
		#define XENGINE_API __declspec(dllexport)
	#else 
		#define XENGINE_API __declspec(dllimport)
	#endif
#else
	#error XEngine only supports Windows now!
#endif

#define BIT(x) (1 << x)