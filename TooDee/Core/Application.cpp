#include <filesystem>
#include <iostream>
#include "TooDee/Core/Application.h"
#include "TooDee/Core/Log.h"
#include "TooDee/Renderer/RendererAPI.h"

namespace TooDee
{
    Application* Application::s_instance = nullptr;

    Application::Application(const ApplicationSpecification& spec)
        : m_specification(spec)
    {

        s_instance = this;

        if (!m_specification.workingDirectory.empty())
        {
            std::filesystem::current_path(m_specification.workingDirectory);
        }

        m_window = Window::Create(WindowProps(m_specification.name));
        m_window->SetEventCallback(TD_BIND_EVENT_FN(Application::OnEvent));
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

#if 0
        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
        {
            if (e.Handled)
                break;
            (*it)->OnEvent(e);
        }
#endif
    }

    void Application::Run()
    {
        while (m_running)
        {
            if (!m_minimized)
            {
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
