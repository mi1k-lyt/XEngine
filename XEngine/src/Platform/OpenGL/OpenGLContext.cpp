#include "Pch.h"
#include "Platform/OpenGL/OpenGLContext.h"


#include <GLFW/glfw3.h>
#include <glad/glad.h>




namespace XEngine {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		XENGINE_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		// Create Context
		glfwMakeContextCurrent(m_WindowHandle);
		// Init Glad
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		XENGINE_CORE_ASSERT(status, "Failed to initialize Glad!");

		XENGINE_CORE_INFO("OpenGL Info:");
		XENGINE_CORE_INFO("Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		XENGINE_CORE_INFO("Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		XENGINE_CORE_INFO("Version: {0}", (const char*)glGetString(GL_VERSION));

		XENGINE_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "requires at least OpenGL version 4.5!");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}