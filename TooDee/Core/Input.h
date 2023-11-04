#pragma once

#include "TooDee/Core/KeyCodes.h"
#include "TooDee/Core/MouseCodes.h"

#include <glm/glm.hpp>

namespace TooDee {
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}
