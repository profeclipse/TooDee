#include "TooDee/Core/Window.h"

#ifdef TD_PLATFORM_MACOS
    #include "TooDee/Platform/MacOS/MacOSWindow.h"
#endif

namespace TooDee
{
    Scope<Window> Window::Create(const WindowProps& props)
    {
#ifdef TD_PLATFORM_MACOS
        return CreateScope<MacOSWindow>(props);
#else
        TD_CORE_ASSERT(false,"Unknown platform!");
        return nullptr;
#endif
    }
}
