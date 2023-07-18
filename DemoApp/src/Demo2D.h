#pragma once

#include "XEngine.h"

class Demo2D : public XEngine::Layer
{
public:
	Demo2D();
	virtual ~Demo2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(XEngine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(XEngine::Event& e) override;
private:
	XEngine::Ref<XEngine::Shader> m_FlatColorShader;
	XEngine::Ref<XEngine::VertexArray> m_SquareVA;

	XEngine::Ref<XEngine::Texture2D> m_Texture, m_ChernoLogoTexture;

	XEngine::OrthographicCameraController m_CameraController;
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

};

