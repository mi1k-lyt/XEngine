#include "Pch.h"
#include "XEngine/Renderer/Buffer.h"

#include "XEngine/Renderer/Renderer.h"

namespace XEngine {

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		/*switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    XENGINE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexBuffer>(size);
		}

		XENGINE_CORE_ASSERT(false, "Unknown RendererAPI!");*/
		return nullptr;
	}

}
