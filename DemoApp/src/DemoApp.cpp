#include <XEngine.h>
#include <imgui.h>

class ExampleLayer : public XEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		//XENGINE_INFO("ExampleLayer::Update");
		
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("text");
		ImGui::Text("hello word!");
		ImGui::End();
	}

	void OnEvent(XEngine::Event& event) override
	{
		/*if (event.GetEventType() == XEngine::EventType::KeyPressed)
		{
			XEngine::KeyPressedEvent& e = (XEngine::KeyPressedEvent&)event;
			XENGINE_TRACE("{0}", (char)e.GetKeyCode());
		}*/
		//XENGINE_TRACE("{0}", event);
	}
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
