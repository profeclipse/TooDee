#pragma once

#include <string>
#include "TooDee/Core/Base.h"
#include "TooDee/Core/Window.h"
#include "TooDee/Core/LayerStack.h"
#include "TooDee/ImGui/ImGuiLayer.h"
#include "TooDee/Events/Event.h"
#include "TooDee/Events/ApplicationEvent.h"

int main(int argc,char **argv);

namespace TooDee
{
    struct ApplicationCommandLineArgs
    {
        int count = 0;
        char **args = nullptr;

        const char* operator[](int index) const
        {
            return args[index];
        }
    };

    struct ApplicationSpecification
    {
        std::string name = "TooDee Application";
        std::string workingDirectory;
        ApplicationCommandLineArgs commandLineArgs;
    };

    class Application
    {
        public:
            Application(const ApplicationSpecification& spec);
            virtual ~Application();

            void OnEvent(Event& e);

            void PushLayer(Layer* layer);
            void PushOverlay(Layer* layer);

            void Close();

            ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

            static Application& Get()	{ return *s_instance; }

            const ApplicationSpecification& GetSpecification() const
            {
                return m_specification;
            }
            Window& GetWindow() 		{ return *m_window; }

        private:
            void Run();
            bool OnWindowClose(WindowCloseEvent& e);
            bool OnWindowResize(WindowResizeEvent& e);

        private:
            ApplicationSpecification m_specification;
            Scope<Window> m_window;
            ImGuiLayer* m_ImGuiLayer;
            bool m_running = true;
            bool m_minimized = false;
            LayerStack m_layerStack;
            float m_lastFrameTime = 0.0f;

        private:
            static Application* s_instance;
            friend int ::main(int argc,char** argv);
    };

    Application* CreateApplication(ApplicationCommandLineArgs args);
}
