#pragma once

#include "XEngine/Renderer/OrthographicCamera.h"

#include "XEngine/Renderer/Texture.h"

#include "XEngine/Renderer/Camera.h"
#include "XEngine/Renderer/EditorCamera.h"
#include "XEngine/Renderer/Font.h"


namespace XEngine {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();


		static void BeginScene(const OrthographicCamera& camera); // TODO: Remove
		static void EndScene();

		// Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

	};

}