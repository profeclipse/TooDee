#include <filesystem>
#include <iostream>
#include "TooDee/Core/Application.h"
#include "TooDee/Core/Log.h"
#include "TooDee/Renderer/RendererAPI.h"
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

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        glGenVertexArrays(1,&m_vertexArray);
        glBindVertexArray(m_vertexArray);

        glGenBuffers(1,&m_vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER,m_vertexBuffer);

        float vertices[3*3] = {
            -0.5f,-0.5f,0.0f,
             0.5f,-0.5f,0.0f,
             0.0f, 0.5f,0.0f
        };

        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),nullptr);

        glGenBuffers(1,&m_indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_indexBuffer);

        unsigned int indices[3] = {
            0,1,2
        };

        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

        std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		//m_shader = Shader::Create("default",vertexSrc, fragmentSrc);
        m_shader = Shader::Create("assets/shaders/FlatColor.glsl");
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
        dispatcher.Dispatch<WindowCloseEvent>(TD_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(TD_BIND_EVENT_FN(Application::OnWindowResize));

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
                {
                    glClearColor(0.0,0.3,0.3,1);
                    glClear(GL_COLOR_BUFFER_BIT);

                    m_shader->Bind();
                    m_shader->SetFloat4("u_Color",{0.2f,0.4f,0.8f,1.0f});
                    glBindVertexArray(m_vertexArray);
                    glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,nullptr);

                    for (Layer* layer : m_layerStack)
                    {
                        layer->OnUpdate(timestep);
                    }
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
        //Renderer::OnWindowResize(e.GetWidth(),e.GetHeight());

        return false;
    }
}
