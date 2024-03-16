#include <imgui/imgui.h>
#include "ExampleLayer.h"

using namespace TooDee;

ExampleLayer::ExampleLayer()
    : Layer("Example"), m_camera(-1.6f,1.6f,-0.9f,0.9f),m_cameraPosition(0.0f,0.0f,0.0f)
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

    m_squareVertexArray = VertexArray::Create();

    float squareVertices[5*4] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };

    Ref<VertexBuffer> squareVertexBuffer = VertexBuffer::Create(squareVertices,
            sizeof(squareVertices));

    squareVertexBuffer->SetLayout({
            { TooDee::ShaderDataType::Float3, "a_Position" },
            { TooDee::ShaderDataType::Float2, "a_TexCoord" }
    });
    m_squareVertexArray->AddVertexBuffer(squareVertexBuffer);

    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
    Ref<IndexBuffer> squareIndexBuffer = IndexBuffer::Create(squareIndices,sizeof(squareIndices)/sizeof(uint32_t));
    m_squareVertexArray->SetIndexBuffer(squareIndexBuffer);

    m_shader = Shader::Create("assets/shaders/Default.glsl");
    m_flatColorShader = Shader::Create("assets/shaders/FlatColorTest.glsl");
    m_textureShader = Shader::Create("assets/shaders/TextureTest.glsl");

    m_textureShader->Bind();
    m_textureShader->SetInt("u_Texture",0);

    m_texture = Texture2D::Create("assets/textures/Checkerboard.png");
    //m_texture = Texture2D::Create("assets/textures/ChernoLogo.png");
}

void ExampleLayer::OnUpdate(TooDee::TimeStep ts)
{
    RenderCommand::SetClearColor({0.0,0.3,0.3,1});
    RenderCommand::Clear();

    m_camera.SetPosition(m_cameraPosition);

    Renderer::BeginScene(m_camera);

    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

    m_flatColorShader->Bind();
    m_flatColorShader->SetFloat3("u_Color", m_squareColor);

    for (int y=0; y<20; y++)
    {
        for (int x=0; x<20; x++)
        {
            glm::vec3 pos(x*0.11f,y*0.11f,0.0f);
            glm::mat4 transform = glm::translate(glm::mat4(1.0f),pos) * scale;
            Renderer::Submit(m_flatColorShader,m_squareVertexArray,transform);
        }
    }

    m_texture->Bind();
    Renderer::Submit(m_textureShader,m_squareVertexArray,glm::scale(glm::mat4(1.0f),glm::vec3(1.0f)));

    Renderer::EndScene();

    Renderer::Flush();
}

void ExampleLayer::OnEvent(TooDee::Event& e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<KeyPressedEvent>(TD_BIND_EVENT_FN(
                ExampleLayer::OnKeyPressedEvent));
}

bool ExampleLayer::OnKeyPressedEvent(KeyPressedEvent& e)
{
    if (e.GetKeyCode() == Key::Left)
    {
        m_cameraPosition.x -= m_cameraSpeed;
    }
    else if (e.GetKeyCode() == Key::Right)
    {
        m_cameraPosition.x += m_cameraSpeed;
    }
    else if (e.GetKeyCode() == Key::Down)
    {
        m_cameraPosition.y -= m_cameraSpeed;
    }
    else if (e.GetKeyCode() == Key::Up)
    {
        m_cameraPosition.y += m_cameraSpeed;
    }
    else if (e.GetKeyCode() == Key::Escape)
    {
        Application::Get().Close();
    }

    return false;
}

void ExampleLayer::OnImGuiRender()
{
#if 0
    ImGui::Begin("Stats for Nerds");
    ImGui::Text("Hello, World!");
    ImGui::End();
#endif
}
