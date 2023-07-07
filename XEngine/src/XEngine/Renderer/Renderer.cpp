#include "Pch.h"
#include "XEngine/Renderer/Renderer.h"

namespace XEngine {

	Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::Shutdown()
	{
		
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray)
	{
		RenderCommand::DrawIndexed(vertexArray);
	}

}