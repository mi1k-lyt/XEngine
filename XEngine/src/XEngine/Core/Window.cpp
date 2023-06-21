#include "Pch.h"
#include "XEngine/Core/Window.h"

#ifdef XENGINE_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif

namespace XEngine {

	Scope<Window> Window::Create(const WindowProps& props) {
	#ifdef XENGINE_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
	#else 
		XENGINE_CORE_ASSERT(false, "Unkown Platform!");
		return nullptr;
	#endif
	}

}