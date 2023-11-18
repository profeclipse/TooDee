#pragma once

#include "TooDee/Renderer/RendererAPI.h"

namespace TooDee
{
    class RenderCommand
    {
        public:
            inline static void Clear()
            {
                s_rendererAPI->Clear();
            }

            inline static void SetClearColor(const glm::vec4& color)
            {
                s_rendererAPI->SetClearColor(color);
            }

            inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
            {
                s_rendererAPI->DrawIndexed(vertexArray);
            }

            inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

        private:
            static Scope<RendererAPI> s_rendererAPI;
    };
}
