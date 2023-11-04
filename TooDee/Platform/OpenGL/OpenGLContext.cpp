#include <iostream>
#include "TooDee/Platform/OpenGL/OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace TooDee {
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : m_windowHandle(windowHandle)
    {
        TD_CORE_ASSERT(windowHandle,"Window handle is null!")
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_windowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        TD_CORE_ASSERT(status,"Failed to initialize Glad!");

        TD_CORE_INFO("OpenGL Info:");
        TD_CORE_INFO("  Vendor: {0}",reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
        TD_CORE_INFO("  Renderer: {0}",reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
        TD_CORE_INFO("  Version: {0}",reinterpret_cast<const char *>(glGetString(GL_VERSION)));

        TD_CORE_ASSERT(GLVersion.major>4 || (GLVersion.major==4 && GLVersion.minor>=1),
                "TooDee requires at least OpenGL version 4.1!");
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_windowHandle);
    }
}
