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
		m_Window->SetEventCallback(XENGINE_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();
	}

	Application::~Application()
	{
		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(XENGINE_BIND_EVENT_FN(OnWindowClose));
		XENGINE_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
			{
				break;
			}
		}

	}

	void Application::Run()
	{

		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			m_Window->OnUpdate();
		}

	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}