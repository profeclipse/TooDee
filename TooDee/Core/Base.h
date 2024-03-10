#pragma once

#include "TooDee/Core/PlatformDetection.h"

#include <memory>
#include <string>

#ifdef TD_DEBUG
    #if defined(TD_PLATFORM_MACOS) || defined(TD_PLATFORM_LINUX)
        #include <signal.h>
        #define TD_DEBUGBREAK() raise(SIGTRAP)
    #elif defined(TD_PLATFORM_WINDOWS)
        #define TD_DEBUGBREAK() __debugbreak()
    #else
        #error "Platform doesn't support debugbreak yet"
    #endif
    #define TD_ENABLE_ASSERTS
#else
    #define TD_DEBUGBREAK()
#endif

#define TD_EXPAND_MACRO(x) x
#define TD_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define TD_BIND_EVENT_FN(fn) \
    [this](auto&&... args)->decltype(auto) \
    { return this->fn(std::forward<decltype(args)>(args)...); }

namespace TooDee
{
    template<typename T>
        using Scope = std::unique_ptr<T>;
    template<typename T, typename ... Args>
        constexpr Scope<T> CreateScope(Args&& ... args)
        {
            return std::make_unique<T>(std::forward<Args>(args)...);
        }

    template<typename T>
        using Ref = std::shared_ptr<T>;
    template<typename T, typename ... Args>
        constexpr Ref<T> CreateRef(Args&& ... args)
        {
            return std::make_shared<T>(std::forward<Args>(args)...);
        }
}

#include "TooDee/Core/Log.h"
#include "TooDee/Core/Assert.h"
