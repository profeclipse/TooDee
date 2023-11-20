#include <imgui/imgui.h>
#include "ExampleLayer.h"

using namespace TooDee;

ExampleLayer::ExampleLayer()
    : Layer("Example"), m_camera(-1.0f,1.0f,-1.0f,1.0f)
{
    float vertices[3 * 7] = {
        -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
         0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
         0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
    };

    Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices,
            sizeof(vertices));

    vertexBuffer->SetLayout({
            { ShaderDataType::Float3,"a_Position" },
            { ShaderDataType::Float4,"a_Color" }
    });

    uint32_t indices[3] = {
        0,1,2
    };

    Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices,
            sizeof(indices)/sizeof(uint32_t));

    m_vertexArray = VertexArray::Create();
    m_vertexArray->AddVertexBuffer(vertexBuffer);
    m_vertexArray->SetIndexBuffer(indexBuffer);

    m_shader = Shader::Create("assets/shaders/Default.glsl");
}

void ExampleLayer::OnUpdate(TooDee::TimeStep ts)
{
    RenderCommand::SetClearColor({0.0,0.3,0.3,1});
    RenderCommand::Clear();

    Renderer::BeginScene(m_camera);
    Renderer::Submit(m_shader,m_vertexArray);
    Renderer::EndScene();

    Renderer::Flush();
}

void ExampleLayer::OnEvent(TooDee::Event& e)
{
}

void ExampleLayer::OnImGuiRender()
{
    ImGui::Begin("Stats for Nerds");
    ImGui::Text("Hello, World!");
    ImGui::End();
}
