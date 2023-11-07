set(SOURCES
    imconfig.h
    imgui.h
    imgui.cpp
    imgui_draw.cpp
    imgui_internal.h
    imgui_widgets.cpp
    imstb_rectpack.h
    imstb_textedit.h
    imstb_truetype.h
    imgui_tables.cpp
    imgui_demo.cpp
    )

add_library(imgui STATIC
    ${SOURCES}
    )
add_library(toodee::imgui ALIAS imgui)

target_include_directories(imgui
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../glfw/include>
    )

target_sources(imgui PUBLIC
    FILE_SET HEADERS
    FILES
    imconfig.h
    imgui.h
    imgui_internal.h
    imstb_rectpack.h
    imstb_textedit.h
    imstb_truetype.h
    #    backends/imgui_impl_glfw.h
    #    backends/imgui_impl_opengl3.h
    )
