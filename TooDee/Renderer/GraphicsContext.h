#pragma once

#include "TooDee/Core/Base.h"
#include "TooDee/Renderer/Renderer.h"

namespace TooDee {
    class GraphicsContext
    {
        public:
            virtual ~GraphicsContext() = default;

            virtual void Init() = 0;
            virtual void SwapBuffers() = 0;

            static Scope<GraphicsContext> Create(void* window);
    };
}
