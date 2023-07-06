#include "Pch.h"
#include "XEngine/Renderer/VertexArray.h"

#include "XEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"


namespace XEngine {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    XENGINE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
		}

			XENGINE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
