#include <XEngine.h>
#include <imgui.h>


class ExampleLayer : public XEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		m_VertexArray = XEngine::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 1.0f, 1.0f
		};

		XEngine::Ref<XEngine::VertexBuffer> vertexBuffer;

		vertexBuffer = XEngine::VertexBuffer::Create(vertices, sizeof(vertices));

		{
			XEngine::BufferLayout layout = {
				{ XEngine::ShaderDataType::Float3, "a_Position" },
				{ XEngine::ShaderDataType::Float4, "a_Color" }
			};
			vertexBuffer->SetLayout(layout);
		}

		m_VertexArray->AddVertexBuffer(vertexBuffer);


		XEngine::Ref<XEngine::IndexBuffer> indexBuffer;

		uint32_t indices[3] = { 2, 1, 0 };
		indexBuffer = XEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

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

		m_Shader.reset(new XEngine::Shader(vertexSrc, fragmentSrc));
	}

	void OnUpdate() override
	{
		if (XEngine::Input::IsKeyPressed(XEngine::Key::A))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed;
		}
		else if (XEngine::Input::IsKeyPressed(XEngine::Key::D))
		{
			m_CameraPosition.x += m_CameraMoveSpeed;
		}

		if (XEngine::Input::IsKeyPressed(XEngine::Key::W))
		{
			m_CameraPosition.y += m_CameraMoveSpeed;
		}
		else if (XEngine::Input::IsKeyPressed(XEngine::Key::S))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed;
		}


		if (XEngine::Input::IsKeyPressed(XEngine::Key::Left))
		{
			m_CameraRotation -= m_CameraRotationSpeed;
		}
		else if (XEngine::Input::IsKeyPressed(XEngine::Key::Right))
		{
			m_CameraRotation += m_CameraRotationSpeed;
		}


		XEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		XEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		XEngine::Renderer::BeginScene(m_Camera);

		XEngine::Renderer::Submit(m_Shader, m_VertexArray);

		XEngine::Renderer::EndScene();
		
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("text");
		ImGui::Text("hello word!");
		ImGui::End();
	}

	void OnEvent(XEngine::Event& event) override
	{
		
	}

	
	XEngine::Ref<XEngine::Shader> m_Shader;
	XEngine::Ref<XEngine::VertexArray> m_VertexArray;

	XEngine::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	float m_CameraMoveSpeed = 0.0001f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 0.01f;
};

class Demo : public XEngine::Application
{
public:
	Demo()
	{
		PushLayer(new ExampleLayer());
	}

	~Demo()
	{
	
	}

};

XEngine::Application* XEngine::CreateApplication()
{
	return new Demo();
}
