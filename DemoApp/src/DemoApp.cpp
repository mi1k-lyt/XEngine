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
			uniform mat4 u_Transform;
			

			out vec3 v_Position;
			out vec4 v_Color;		

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
			}

		)";

		std::string fragmentSrc = R"(
			#version 460 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec4 u_Color;

			void main()
			{
				color = u_Color;
			}

		)";

		m_Shader.reset(new XEngine::Shader(vertexSrc, fragmentSrc));
	}

	void OnUpdate(XEngine::Timestep timestep) override
	{	
		if (XEngine::Input::IsKeyPressed(XEngine::Key::A))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * timestep;
		}
		else if (XEngine::Input::IsKeyPressed(XEngine::Key::D))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * timestep;
		}

		if (XEngine::Input::IsKeyPressed(XEngine::Key::W))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * timestep;
		}
		else if (XEngine::Input::IsKeyPressed(XEngine::Key::S))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * timestep;
		}


		if (XEngine::Input::IsKeyPressed(XEngine::Key::Left))
		{
			m_CameraRotation -= m_CameraRotationSpeed * timestep;
		}
		else if (XEngine::Input::IsKeyPressed(XEngine::Key::Right))
		{
			m_CameraRotation += m_CameraRotationSpeed * timestep;
		}


		XEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		XEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		XEngine::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		glm::vec4 redColor = glm::vec4(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blueColor = glm::vec4(0.2f, 0.3f, 0.8f,  1.0f);

		for (int y = 0; y < 20; ++y)
		{
			for (int x = 0; x < 20; ++x)
			{
				glm::vec3 pos(x * 0.11f + -1.0f, y * 0.11f + -1.0f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				if (x % 2 == y % 2)
				{
					m_Shader->UploadUniformFloat4("u_Color", redColor);
				}
				else
				{
					m_Shader->UploadUniformFloat4("u_Color", blueColor);
				}
				XEngine::Renderer::Submit(m_Shader, m_VertexArray, transform);
			}
		} 

		XEngine::Renderer::EndScene();
		
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Welcome XEngine!");
		ImGui::End();
	}

	void OnEvent(XEngine::Event& event) override
	{
		
	}

	
	XEngine::Ref<XEngine::Shader> m_Shader;
	XEngine::Ref<XEngine::VertexArray> m_VertexArray;

	XEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	float m_CameraMoveSpeed = 1.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 10.0f;

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
