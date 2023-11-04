set(SOURCES
    src/context.c
    src/init.c
    src/input.c
    src/monitor.c
    src/platform.c
    src/vulkan.c
    src/window.c
    src/egl_context.c
    src/osmesa_context.c
    src/null_init.c
    src/null_monitor.c
    src/null_window.c
    src/null_joystick.c
    src/cocoa_time.c
    src/posix_module.c
    src/posix_thread.c
    src/cocoa_init.m
    src/cocoa_joystick.m
    src/cocoa_monitor.m
    src/cocoa_window.m
    src/nsgl_context.m
    )

add_library(glfw3 STATIC
    ${SOURCES}
    )
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
    deps/nuklear_glfw_gl2.h
    deps/linmath.h
    deps/stb_image_write.h
    deps/nuklear.h
    deps/getopt.h
    deps/mingw/dinput.h
    deps/mingw/_mingw_dxhelper.h
    deps/mingw/xinput.h
    deps/glad/vulkan.h
    deps/glad/gl.h
    deps/glad/gles2.h
    deps/tinycthread.h
    deps/vs2008/stdint.h
    src/posix_thread.h
    src/win32_time.h
    src/internal.h
    src/null_platform.h
    src/cocoa_platform.h
    src/xkb_unicode.h
    src/posix_poll.h
    src/x11_platform.h
    src/cocoa_time.h
    src/win32_joystick.h
    src/linux_joystick.h
    src/posix_time.h
    src/mappings.h
    src/cocoa_joystick.h
    src/null_joystick.h
    src/win32_thread.h
    src/wl_platform.h
    src/win32_platform.h
    src/platform.h
    )

target_compile_definitions(glfw3 PRIVATE
    _GLFW_COCOA
    )
