#include <imgui/imgui.h>
#include "ExampleLayer.h"

ExampleLayer::ExampleLayer()
    : Layer("Example")
{
}

void ExampleLayer::OnUpdate(TooDee::TimeStep ts)
{
    //TD_INFO("ExampleLayer::Update");
}

void ExampleLayer::OnEvent(TooDee::Event& e)
{
    //TD_TRACE("{0}",e);
}

void ExampleLayer::OnImGuiRender()
{
    bool state = true;
    //ImGui::ShowDemoWindow(&state);

    //ImGui::Begin("Hello");
    //ImGui::Text("Hello, World!");
    //ImGui::End();
}
