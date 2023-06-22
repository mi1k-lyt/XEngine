#include <XEngine.h>

class ExampleLayer : public XEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		XENGINE_INFO("ExampleLayer::Update");
	}

	void OnEvent(XEngine::Event& event) override
	{
		XENGINE_TRACE("{0}", event);
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
