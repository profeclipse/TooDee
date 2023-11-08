#pragma once

#include "TooDee/Core/Window.h"
#include "TooDee/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace TooDee
{
    class MacOSWindow : public Window
    {
        public:
            MacOSWindow(const WindowProps& props);
            virtual ~MacOSWindow();

            void OnUpdate() override;

            unsigned int GetWidth() const override				{ return m_data.width; }
            unsigned int GetHeight() const override				{ return m_data.height; }

            void SetEventCallback(const EventCallbackFn& callback) override
                    { m_data.eventCallback = callback; }
            void SetVSync(bool enabled) override;
            bool IsVSync() const override;

            virtual void* GetNativeWindow() const override		{ return m_window; }

        private:
            virtual void Init(const WindowProps& props);
            virtual void Shutdown();

        private:
            GLFWwindow* m_window;
            Scope<GraphicsContext> m_context;

            struct WindowData
            {
                std::string title;
                unsigned int width,height;
                bool vSync;
                EventCallbackFn eventCallback;
            };

            WindowData m_data;
    };
}
