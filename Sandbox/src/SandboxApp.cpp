#include <TooDee/TooDee.h>
#include <TooDee/Core/EntryPoint.h>
#include "ExampleLayer.h"

using namespace TooDee;

class SandboxApp : public Application
{
    public:
        SandboxApp(const ApplicationSpecification& spec)
            : Application(spec)
        {
            PushLayer(new ExampleLayer());
        }

        ~SandboxApp()
        {
        }
};

Application* TooDee::CreateApplication(ApplicationCommandLineArgs args)
{
    ApplicationSpecification spec;
    spec.name = "Sandbox";
    spec.workingDirectory = "C:/Users/david/Projects/TooDee/Sandbox";
    spec.commandLineArgs = args;

    return new SandboxApp(spec);
}
