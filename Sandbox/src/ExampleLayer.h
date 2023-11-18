#pragma once

#include <TooDee/TooDee.h>

class ExampleLayer : public TooDee::Layer
{
    public:
        ExampleLayer();

        virtual void OnUpdate(TooDee::TimeStep ts) override;
        virtual void OnEvent(TooDee::Event& e) override;
        virtual void OnImGuiRender() override;

    private:
        TooDee::Ref<TooDee::Shader> m_shader;
        TooDee::Ref<TooDee::VertexArray> m_vertexArray;
        TooDee::OrthographicCamera m_camera;
};
