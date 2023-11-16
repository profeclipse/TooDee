#include "TooDee/Renderer/VertexArray.h"
#include "TooDee/Renderer/Renderer.h"
#include "TooDee/Platform/OpenGL/OpenGLVertexArray.h"

namespace TooDee
{
    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                TD_CORE_ASSERT(false,"RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLVertexArray>();
        }
    }
}
