#include <filesystem>
#include <iostream>
#include "TooDee/Core/Application.h"
#include "TooDee/Core/Log.h"
#include "TooDee/Renderer/Renderer.h"
#include "TooDee/Core/TimeStep.h"
#include "TooDee/Utils/PlatformUtils.h"

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
            (*it)->OnEvent(e);
            if (e.Handled)
                break;
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
