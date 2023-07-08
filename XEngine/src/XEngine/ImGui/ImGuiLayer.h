#pragma once

#include "XEngine/Core/Layer.h"

#include "XEngine/Events/ApplicationEvent.h"
#include "XEngine/Events/KeyEvent.h"
#include "XEngine/Events/MouseEvent.h"

namespace XEngine {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

		void SetDarkThemeColors();

		uint32_t GetActiveWidgetID() const;
	private:
		


	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};

}
