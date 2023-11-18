#include <imgui/imgui.h>
#include "ExampleLayer.h"

using namespace TooDee;

ExampleLayer::ExampleLayer()
    : Layer("Example"), m_camera(0.0f,1600.0f,0.0f,900.0f)
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

    std::string vertexSrc = R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;

		out vec3 v_Position;
        out vec4 v_Color;

		void main()
		{
			v_Position = a_Position;
            v_Color = a_Color;
			gl_Position = vec4(a_Position, 1.0);
		}
	)";

    std::string fragmentSrc = R"(
		#version 330 core

		layout(location = 0) out vec4 color;

		in vec3 v_Position;
        in vec4 v_Color;

		void main()
		{
			//color = vec4(v_Position * 0.5 + 0.5, 1.0);
            color = v_Color;
		}
	)";

    m_shader = Shader::Create("default",vertexSrc, fragmentSrc);
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
    //bool state = true;
    //ImGui::ShowDemoWindow(&state);

    ImGui::Begin("Hello");
    ImGui::Text("Hello, World!");
    ImGui::End();
}
