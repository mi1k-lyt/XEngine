#include "Pch.h"
#include "XEngine/Core/Application.h"

#include "XEngine/Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>


namespace XEngine {

	Application::Application()
	{
		m_Window = Window::Create();
	}

	Application::~Application()
	{
	
	}

	void Application::Run()
	{

		while (m_Running)
		{
			m_Window->OnUpdate();
		}

	}

}