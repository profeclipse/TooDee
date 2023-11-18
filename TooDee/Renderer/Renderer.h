#pragma once

#include "TooDee/Renderer/OrthographicCamera.h"
#if 0
#include "TooDee/Renderer/RenderCommand.h"
#endif
#include "TooDee/Renderer/Shader.h"

#include "TooDee/Renderer/RendererAPI.h"

namespace TooDee {

    class Renderer
    {
        public:
            static void Init();
            static void Shutdown();

            static void OnWindowResize(uint32_t width, uint32_t height);

            static void BeginScene(OrthographicCamera& camera);
            static void EndScene();
            static void Flush();

            static void Submit(const Ref<Shader>& shader,
                    const Ref<VertexArray>& vertexArray,
                    const glm::mat4& transform=glm::mat4(1.0f));

            static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
        private:
            struct SceneData
            {
                glm::mat4 viewProjectionMatrix;
            };

            static Scope<SceneData> s_sceneData;
    };
}
