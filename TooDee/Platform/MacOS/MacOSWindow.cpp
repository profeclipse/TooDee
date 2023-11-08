#include <iostream>
#include <GLFW/glfw3.h>
#include "TooDee/Platform/MacOS/MacOSWindow.h"
#include "TooDee/Events/ApplicationEvent.h"
#include "TooDee/Events/KeyEvent.h"
#include "TooDee/Events/MouseEvent.h"

namespace TooDee
{
    static uint16_t s_windowCount = 0;

    static void GLFWErrorCallback(int error,const char* description)
    {
        TD_CORE_ERROR("GLFW Error ({0}): {1}",error,description);
    }

    MacOSWindow::MacOSWindow(const WindowProps& props)
    {
        Init(props);
    }

    MacOSWindow::~MacOSWindow()
    {
        Shutdown();
    }

    void MacOSWindow::OnUpdate()
    {
        glfwPollEvents();
        m_context->SwapBuffers();
    }

    void MacOSWindow::SetVSync(bool enabled)
    {
        if (enabled)
        {
            glfwSwapInterval(1);
        }
        else
        {
            glfwSwapInterval(0);
        }

        m_data.vSync = enabled;
    }

    bool MacOSWindow::IsVSync() const
    {
        return m_data.vSync;
    }

    void MacOSWindow::Init(const WindowProps& props)
    {
        m_data.title = props.title;
        m_data.height = props.height;
        m_data.width = props.width;

        TD_CORE_INFO("Creating window {0} ({1},{2})",props.title,props.width,props.height);

        if (s_windowCount == 0)
        {
            int success = glfwInit();

            TD_CORE_ASSERT(success,"Could not initialize GLFW!");
            glfwSetErrorCallback(GLFWErrorCallback);
        }

        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GLFW_TRUE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,1);
        glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER,GLFW_FALSE);
        m_window = glfwCreateWindow((int)props.width,(int)props.height,
                m_data.title.c_str(),nullptr,nullptr);
        ++s_windowCount;

        m_context = GraphicsContext::Create(m_window);
        m_context->Init();

        glfwSetWindowUserPointer(m_window,&m_data);

        SetVSync(true);

        glfwSetWindowSizeCallback(m_window,[](GLFWwindow* window,int width,int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;

			WindowResizeEvent event(width,height);
			data.eventCallback(event);
		});

		glfwSetWindowCloseCallback(m_window,[](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.eventCallback(event);
		});

		glfwSetKeyCallback(m_window,[](GLFWwindow* window,int key,int scancode,int action,int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key,0);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.eventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key,true);
					data.eventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_window,[](GLFWwindow* window,unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			data.eventCallback(event);
		});

		glfwSetMouseButtonCallback(m_window,[](GLFWwindow* window,int button,int action,int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.eventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_window,[](GLFWwindow* window,double xOffset,double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset,(float)yOffset);
			data.eventCallback(event);
		});

		glfwSetCursorPosCallback(m_window,[](GLFWwindow* window,double xPos,double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos,(float)yPos);
			data.eventCallback(event);
		});
    }

    void MacOSWindow::Shutdown()
    {
        glfwDestroyWindow(m_window);

        if (--s_windowCount == 0)
        {
            glfwTerminate();
        }
    }
}
