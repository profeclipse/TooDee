#include "TooDee/Utils/PlatformUtils.h"
#include "TooDee/Core/Application.h"

#include <GLFW/glfw3.h>

namespace TooDee {

    float Time::GetTime()
    {
        return glfwGetTime();
    }


    std::string FileDialogs::OpenFile(const char* filter)
    {
        return std::string();
    }

    std::string FileDialogs::SaveFile(const char* filter)
    {
        return std::string();
    }
}
