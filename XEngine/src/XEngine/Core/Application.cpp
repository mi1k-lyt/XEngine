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

		m_VertexArray = VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 1.0f, 1.0f
		};

		Ref<VertexBuffer> vertexBuffer;
		
		vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

		{
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float4, "a_Color" }
			};
			vertexBuffer->SetLayout(layout);
		}

		m_VertexArray->AddVertexBuffer(vertexBuffer);


		Ref<IndexBuffer> indexBuffer;

		uint32_t indices[3] = { 2, 1, 0 };
		indexBuffer = IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t));

		m_VertexArray->SetIndexBuffer(indexBuffer);
	
		std::string vertexSrc = R"(
			#version 460 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;	

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;		

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);
			}

		)";

		std::string fragmentSrc = R"(
			#version 460 core
			
			layout(location = 0) out vec4 color;			
			
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;//vec4(v_Position*0.5+0.5, 1.0);
			}

		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
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
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();

			m_Camera.SetPosition({ 0.5f, 0.5f, 0.0f });
			m_Camera.SetRotation(45.0f);

			Renderer::BeginScene(m_Camera);

			Renderer::Submit(m_Shader, m_VertexArray);

			Renderer::EndScene();

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