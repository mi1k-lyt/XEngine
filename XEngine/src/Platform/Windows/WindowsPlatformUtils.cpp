#include "Pch.h"
#include "XEngine/Utils/PlatformUtils.h"
#include "XEngine/Core/Application.h"

#include <commdlg.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace XEngine {

	float Time::GetTime()
	{
		return glfwGetTime();
	}

}