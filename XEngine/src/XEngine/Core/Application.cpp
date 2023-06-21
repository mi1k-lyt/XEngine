#include "Pch.h"
#include "XEngine/Core/Application.h"

#include "XEngine/Events/ApplicationEvent.h"

#include "XEngine/Renderer/Renderer.h"

#include "XEngine/Core/Input.h"

#include <glad/glad.h>


namespace XEngine {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		XENGINE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::Create();

		Renderer::Init();
	}

	Application::~Application()
	{
		Renderer::Shutdown();
	}

	void Application::Run()
	{

		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}

	}

}