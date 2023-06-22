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
		virtual void OnEvent(Event& e) override;
		void OnUpdate();

		void Begin();
		void End();

		void SetDarkThemeColors();

		uint32_t GetActiveWidgetID() const;
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};

}
