#include "TooDee/Renderer/GraphicsContext.h"
#include "TooDee/Renderer/RendererAPI.h"
#include "TooDee/Platform/OpenGL/OpenGLContext.h"

namespace TooDee {
    Scope<GraphicsContext> GraphicsContext::Create(void* window)
    {
        // TODO: should this be Renderer::GetAPI()???
        switch (RendererAPI::GetAPI())
        {
            case RendererAPI::API::None:
                TD_CORE_ASSERT(false,"RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
        }

        TD_CORE_ASSERT(false,"Unknown RendererAPI!");
        return nullptr;
    }
}
