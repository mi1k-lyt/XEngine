#include "Pch.h"
#include "XEngine/Renderer/GraphicsContext.h"

#include "XEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace XEngine {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    XENGINE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		XENGINE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}