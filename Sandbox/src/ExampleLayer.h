#pragma once

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
            TD_INFO("ExampleLayer::Update");
        }

        virtual void OnEvent(TooDee::Event& e) override
        {
            TD_TRACE("{0}",e);
        }
};
