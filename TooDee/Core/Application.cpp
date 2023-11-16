#include <filesystem>
#include <iostream>
#include "TooDee/Core/Application.h"
#include "TooDee/Core/Log.h"
#include "TooDee/Renderer/RendererAPI.h"
#include "TooDee/Renderer/Renderer.h"
#include "TooDee/Core/TimeStep.h"
#include "TooDee/Utils/PlatformUtils.h"

#include <glad/glad.h>

namespace TooDee
{
    Application* Application::s_instance = nullptr;

    Application::Application(const ApplicationSpecification& spec)
        : m_specification(spec)
    {

        TD_CORE_ASSERT(!s_instance,"Application already exists!");
        s_instance = this;

        if (!m_specification.workingDirectory.empty())
        {
            std::filesystem::current_path(m_specification.workingDirectory);
        }

        m_window = Window::Create(WindowProps(m_specification.name));
        m_window->SetEventCallback(TD_BIND_EVENT_FN(Application::OnEvent));

        m_rendererAPI = RendererAPI::Create();
        m_rendererAPI->SetClearColor({0.0,0.3,0.3,1});

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        m_vertexBuffer = VertexBuffer::Create(vertices,sizeof(vertices));

        {
            BufferLayout layout = {
                { ShaderDataType::Float3,"a_Position" },
                { ShaderDataType::Float4,"a_Color" }
            };

            m_vertexBuffer->SetLayout(layout);
        }

        uint32_t indices[3] = {
            0,1,2
        };

        m_indexBuffer = IndexBuffer::Create(indices,sizeof(indices)/sizeof(uint32_t));

        m_vertexArray = VertexArray::Create();
        m_vertexArray->AddVertexBuffer(m_vertexBuffer);
        m_vertexArray->SetIndexBuffer(m_indexBuffer);

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

    Application::~Application()
    {
    }

    void Application::Close()
    {
        m_running = false;
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(
                TD_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(
                TD_BIND_EVENT_FN(Application::OnWindowResize));

        for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); ++it)
        {
            if (e.Handled)
                break;
            (*it)->OnEvent(e);
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        m_layerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_layerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::Run()
    {
        while (m_running)
        {
            float time = Time::GetTime();
            TimeStep timestep = time - m_lastFrameTime;
            m_lastFrameTime = time;

            if (!m_minimized)
            {
                m_rendererAPI->Clear();

                m_shader->Bind();
                m_vertexArray->Bind();
                glDrawElements(GL_TRIANGLES,m_indexBuffer->GetCount(),GL_UNSIGNED_INT,
                        nullptr);

                for (Layer* layer : m_layerStack)
                {
                    layer->OnUpdate(timestep);
                }

                m_ImGuiLayer->Begin();
                {
                    for (Layer* layer : m_layerStack)
                    {
                        layer->OnImGuiRender();
                    }
                }
                m_ImGuiLayer->End();
            }

            m_window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        if (e.GetWidth() == 0 || e.GetHeight() == 0)
        {
            m_minimized = true;
            return false;
        }

        m_minimized = false;
        Renderer::OnWindowResize(e.GetWidth(),e.GetHeight());

        return false;
    }
}
