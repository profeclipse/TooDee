#include "TooDee/Renderer/Renderer.h"
#include "TooDee/Renderer/RenderCommand.h"
#if 0
#include "TooDee/Renderer/Renderer2D.h"
#endif

namespace TooDee {

    Scope<Renderer::SceneData> Renderer::s_sceneData = CreateScope<Renderer::SceneData>();

    void Renderer::Init()
    {
#if 0
        RenderCommand::Init();
        Renderer2D::Init();
#endif
    }

    void Renderer::Shutdown()
    {
#if 0
        Renderer2D::Shutdown();
#endif
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
#if 0
        RenderCommand::SetViewport(0, 0, width, height);
#endif
    }

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        s_sceneData->viewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Flush()
    {
    }

    void Renderer::Submit(const Ref<Shader>& shader,const Ref<VertexArray>& vertexArray,
            const glm::mat4& transform)
    {
        shader->Bind();
        shader->SetMat4("u_ViewProjection",s_sceneData->viewProjectionMatrix);
        shader->SetMat4("u_Transform",transform);

        RenderCommand::DrawIndexed(vertexArray);
    }
}
