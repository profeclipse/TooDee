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
        TooDee::Ref<TooDee::Shader> m_flatColorShader;
        TooDee::Ref<TooDee::Shader> m_textureShader;
        TooDee::Ref<TooDee::VertexArray> m_vertexArray;
        TooDee::Ref<TooDee::VertexArray> m_squareVertexArray;
        TooDee::OrthographicCamera m_camera;
        TooDee::Ref<TooDee::Texture2D> m_texture;
        glm::vec3 m_cameraPosition;
        float m_cameraSpeed = 0.1f;
        glm::vec3 m_squareColor = { 0.8f,0.0f,0.0f };
};
