add_library(glfw3 STATIC)
add_library(toodee::glfw3 ALIAS glfw3)

target_include_directories(glfw3 PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )

target_sources(glfw3 PUBLIC
    FILE_SET HEADERS
    FILES
    include/GLFW/glfw3.h
    include/GLFW/glfw3native.h
    )

target_sources(glfw3 PRIVATE
    src/context.c
    src/init.c
    src/input.c
    src/monitor.c
    src/platform.c
    src/vulkan.c
    src/window.c
    src/egl_context.c
    src/osmesa_context.c
    src/null_joystick.c
    src/null_init.c
    src/null_monitor.c
    src/null_window.c
    src/win32_init.c
    src/win32_module.c
    src/win32_joystick.c
    src/win32_monitor.c
    src/win32_time.c
    src/win32_thread.c
    src/win32_window.c
    src/wgl_context.c
    src/egl_context.c
    src/osmesa_context.c
    )

target_compile_definitions(glfw3 PRIVATE
    _GLFW_WIN32
    _CRT_SECURE_NO_WARNINGS
    )
