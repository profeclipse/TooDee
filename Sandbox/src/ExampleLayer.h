#pragma once

#include <TooDee/TooDee.h>

class ExampleLayer : public TooDee::Layer
{
    public:
        ExampleLayer();

        virtual void OnUpdate(TooDee::TimeStep ts) override;
        virtual void OnEvent(TooDee::Event& e) override;
        bool OnKeyPressedEvent(TooDee::KeyPressedEvent& e);
        virtual void OnImGuiRender() override;

    private:
        TooDee::Ref<TooDee::Shader> m_shader;
        TooDee::Ref<TooDee::VertexArray> m_vertexArray;
        TooDee::OrthographicCamera m_camera;
        glm::vec3 m_cameraPosition;
        float m_cameraSpeed = 0.1f;
};
