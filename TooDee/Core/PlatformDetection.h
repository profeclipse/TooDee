#pragma once

#if defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR == 1
        #error "IOS simiulator not supported"
    #elif TARGET_OS_IPHONE
        #error "IOS not supported"
    #elif TARGET_OS_MAC == 1
        #define TD_PLATFORM_MACOS
    #else
        #error "Unknown Apple platform"
    #endif
#elif _WIN32
    #define TD_PLATFGORM_WINDOWS
    #error "Windows not supported"
#elif defined(__ANDROID__)
    #define TD_PLATFORM_ANDROID
    #error "Android not supported"
#elif defined(__EMSCRIPTEN__)
    #define TD_PLATFORM_EMSCRIPTEN
    #error "Emscripten not supported"
#elif defined(__linux__)
    #define TD_PLATFORM_LINUX
    #error "Linux not supported"
#else
    #error "Unknown platform"
#endif
