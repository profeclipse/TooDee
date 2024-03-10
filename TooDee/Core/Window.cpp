#include "TooDee/Core/Window.h"

#if defined(TD_PLATFORM_WINDOWS)
    #include "TooDee/Platform/Win32/Win32Window.h"
#elif defined(TD_PLATFORM_MACOS)
    #include "TooDee/Platform/MacOS/MacOSWindow.h"
#endif

namespace TooDee
{
    Scope<Window> Window::Create(const WindowProps& props)
    {
#if defined(TD_PLATFORM_WINDOWS)
        return CreateScope<Win32Window>(props);
#elif defined(TD_PLATFORM_MACOS)
        return CreateScope<MacOSWindow>(props);
#else
        TD_CORE_ASSERT(false,"Unknown platform!");
        return nullptr;
#endif
    }
}
