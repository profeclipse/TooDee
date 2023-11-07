#pragma once

#include <imgui/imgui.h>
#include <TooDee/TooDee.h>

class ExampleLayer : public TooDee::Layer
{
    public:
        ExampleLayer()
            : Layer("Example")
        {
        }

        virtual void OnUpdate(TooDee::TimeStep ts) override
        {
            //TD_INFO("ExampleLayer::Update");
        }

        virtual void OnEvent(TooDee::Event& e) override
        {
            //TD_TRACE("{0}",e);
        }

        virtual void OnImGuiRender() override
        {
            bool state = true;
            ImGui::ShowDemoWindow(&state);

            ImGui::Begin("Hello");
            ImGui::Text("Hello, World!");
            ImGui::End();
        }
};
