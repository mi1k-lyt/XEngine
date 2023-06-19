#pragma once

#include "XEngine/Core/Core.h"
#include "XEngine/Events/Event.h"

namespace XEngine {

	class XENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in Client
	Application* CreateApplication();

}

