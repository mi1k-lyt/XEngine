#include <XEngine.h>

// ----------Entry Point--------------
#include <XEngine/Core/EntryPoint.h>
// -----------------------------------


#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Demo2D.h"
#include "ExampleLayer.h"


class Demo : public XEngine::Application
{
public:
	Demo()
	{
		PushLayer(new Demo2D());
		//PushLayer(new ExampleLayer());
	}

	~Demo()
	{
	
	}

};

XEngine::Application* XEngine::CreateApplication()
{
	return new Demo();
}
