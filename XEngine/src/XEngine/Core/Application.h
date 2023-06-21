#pragma once


#include "XEngine/Core/Core.h"


#include "XEngine/Core/Window.h"
#include "XEngine/Events/Event.h"

int main(int argc, char** argv);

namespace XEngine {

	class XENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		static Application& Get() { return *s_Instance; }

		Window& GetWindow() { return *m_Window; }

	private:
		void Run();
	private:
		Scope<Window> m_Window;
		bool m_Running = true;
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	// To be defined in Client
	Application* CreateApplication();

}

