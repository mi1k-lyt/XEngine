#pragma once

#include "XEngine/Core/Core.h"

#include "XEngine/Core/Window.h"
#include "XEngine/Core/LayerStack.h"
#include "XEngine/Events/Event.h"
#include "XEngine/Events/ApplicationEvent.h"

#include "XEngine/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace XEngine {

	class XENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		static Application& Get() { return *s_Instance; }

		Window& GetWindow() { return *m_Window; }

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		void Close();

		
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);


		void Run();
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	// To be defined in Client
	Application* CreateApplication();

}

