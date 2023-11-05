#pragma once

#include "TooDee/Core/Base.h"
#include "TooDee/Core/Application.h"
#include "TooDee/Core/Log.h"

extern TooDee::Application* TooDee::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
    TooDee::Log::Init();

    auto app = TooDee::CreateApplication({argc,argv});

    app->Run();

    delete app;
}