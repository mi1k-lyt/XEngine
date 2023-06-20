#pragma once

#include "XEngine/Core/Core.h"
#include "XEngine/Events/Event.h"
#include "XEngine/Core/Window.h"

namespace XEngine {

	class XENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		Scope<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in Client
	Application* CreateApplication();

}

