#include "TooDee.h"
#include "TooDee/Core/EntryPoint.h"

using namespace TooDee;

class SandboxApp : public Application
{
    public:
        SandboxApp(const ApplicationSpecification& spec)
            : Application(spec)
        {
        }

        ~SandboxApp()
        {
        }
};

Application* TooDee::CreateApplication(ApplicationCommandLineArgs args)
{
    ApplicationSpecification spec;
    spec.name = "Sandbox";
    spec.workingDirectory = "/Users/davidhunt/Projects/TooDee/Sandbox";
    spec.commandLineArgs = args;

    return new SandboxApp(spec);
}
