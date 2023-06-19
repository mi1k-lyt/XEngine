#include "Application.h"

#include "XEngine/Events/ApplicationEvent.h"
#include "XEngine/Core/Log.h"

namespace XEngine {

	Application::Application()
	{

	}

	Application::~Application()
	{
	
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		XENGINE_TRACE(e);

		while (true);
	}

}