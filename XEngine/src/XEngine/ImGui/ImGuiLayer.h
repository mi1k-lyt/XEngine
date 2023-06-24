#pragma once

#include "XEngine/Core/Layer.h"

#include "XEngine/Events/ApplicationEvent.h"
#include "XEngine/Events/KeyEvent.h"
#include "XEngine/Events/MouseEvent.h"

namespace XEngine {

	class XENGINE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void SetDarkThemeColors();

		uint32_t GetActiveWidgetID() const;
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);

		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);

		bool OnWindowResizeEvent(WindowResizeEvent& e);


	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};

}
