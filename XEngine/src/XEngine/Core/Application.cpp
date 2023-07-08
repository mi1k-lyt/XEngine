#include "Pch.h"
#include "XEngine/Core/Application.h"

#include "XEngine/Events/ApplicationEvent.h"

#include "XEngine/Renderer/Renderer.h"

#include "XEngine/Core/Input.h"

#include <glad/glad.h>




namespace XEngine {

	Application* Application::s_Instance = nullptr;

	Application::Application()
		:m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		XENGINE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(XENGINE_BIND_EVENT_FN(Application::OnEvent));

		//Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		
	}

	Application::~Application()
	{
		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(XENGINE_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(XENGINE_BIND_EVENT_FN(Application::OnWindowResize));
		//XENGINE_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.Handled)
				break;
			(*it)->OnEvent(e);
		}

	}

	void Application::Run()
	{

		while (m_Running)
		{
			/*RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();

			m_Camera.SetPosition({ 0.5f, 0.5f, 0.0f });
			m_Camera.SetRotation(45.0f);

			Renderer::BeginScene(m_Camera);

			Renderer::Submit(m_Shader, m_VertexArray);

			Renderer::EndScene();*/

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			{
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();

		}

	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			return false;
		}

		
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

}