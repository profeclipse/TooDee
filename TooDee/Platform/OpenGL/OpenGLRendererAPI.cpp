#include <glad/glad.h>
#include "TooDee/Platform/OpenGL/OpenGLRendererAPI.h"

namespace TooDee {
#if 0
    void OpenGLMessageCallback(
            unsigned source,
            unsigned type,
            unsigned id,
            unsigned severity,
            int length,
            const char* message,
            const void* userParam)
    {
        switch (severity)
        {
            case GL_DEBUG_SEVERITY_HIGH:         TD_CORE_CRITICAL(message); return;
            case GL_DEBUG_SEVERITY_MEDIUM:       TD_CORE_ERROR(message); return;
            case GL_DEBUG_SEVERITY_LOW:          TD_CORE_WARN(message); return;
            case GL_DEBUG_SEVERITY_NOTIFICATION: TD_CORE_TRACE(message); return;
        }

        TD_CORE_ASSERT(false, "Unknown severity level!");
    }
#endif

    void OpenGLRendererAPI::Init()
    {
#ifdef TD_DEBUG
#if 0
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(OpenGLMessageCallback,nullptr);

        glDebugMessageControl(GL_DONT_CARE,GL_DONT_CARE,GL_DEBUG_SEVERITY_NOTIFICATION,0,
                NULL, GL_FALSE);
#endif
#endif

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LINE_SMOOTH);

        SetClearColor({0.0f,1.0f,0.0f,1.0f});
    }

    void OpenGLRendererAPI::SetViewport(uint32_t x,uint32_t y,
            uint32_t width,uint32_t height)
    {
        glViewport(x,y,width,height);
    }

    void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.r,color.g,color.b,color.a);
    }

    void OpenGLRendererAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

#if 0
    void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray,
            uint32_t indexCount)
    {
        vertexArray->Bind();
        uint32_t count = indexCount ?
            indexCount : vertexArray->GetIndexBuffer()->GetCount();
        glDrawElements(GL_TRIANGLES,count,GL_UNSIGNED_INT,nullptr);
    }

    void OpenGLRendererAPI::DrawLines(const Ref<VertexArray>& vertexArray,
            uint32_t vertexCount)
    {
        vertexArray->Bind();
        glDrawArrays(GL_LINES,0,vertexCount);
    }
#endif

    void OpenGLRendererAPI::SetLineWidth(float width)
    {
        glLineWidth(width);
    }
}
