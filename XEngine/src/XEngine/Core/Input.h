#pragma once

#include "XEngine/Core/KeyCodes.h"
#include "XEngine/Core/MouseCodes.h"

#include <glm/glm.hpp>

namespace XEngine {

	class XENGINE_API Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}
