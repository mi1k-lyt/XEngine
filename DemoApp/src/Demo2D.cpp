#include "Demo2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Demo2D::Demo2D()
	: Layer("Demo2D"), m_CameraController(1280.0f / 720.0f), m_SquareColor({ 0.2f, 0.3f, 0.8f, 1.0f })
{
}

void Demo2D::OnAttach()
{
	

}

void Demo2D::OnDetach()
{
	
}

void Demo2D::OnUpdate(XEngine::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	XEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	XEngine::RenderCommand::Clear();

	XEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
	XEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_SquareColor);
	XEngine::Renderer2D::EndScene();
}

void Demo2D::OnImGuiRender()
{

	ImGui::Begin("Settings");

	/*auto stats = XEngine::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());*/

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Demo2D::OnEvent(XEngine::Event& e)
{
	m_CameraController.OnEvent(e);
}