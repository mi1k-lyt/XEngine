#include "Pch.h"
#include "XEngine/Renderer/RenderCommand.h"

namespace XEngine {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}