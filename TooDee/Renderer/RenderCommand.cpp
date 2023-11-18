#include "TooDee/Renderer/RenderCommand.h"

namespace TooDee
{
    Scope<RendererAPI> RenderCommand::s_rendererAPI = RendererAPI::Create();
}
