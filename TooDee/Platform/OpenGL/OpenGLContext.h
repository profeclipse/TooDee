#pragma once

#include "TooDee/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace TooDee
{
    class OpenGLContext : public GraphicsContext
    {
        public:
            OpenGLContext(GLFWwindow* windowHandle);

            virtual void Init() override;
            virtual void SwapBuffers() override;
        private:
            GLFWwindow* m_windowHandle;
    };
}
