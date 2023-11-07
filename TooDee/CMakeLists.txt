add_library(toodee STATIC)
add_library(toodee::toodee ALIAS toodee)

target_sources(toodee PUBLIC
    FILE_SET HEADERS
    FILES
    TooDee.h
    )

add_subdirectory(Core)
add_subdirectory(Events)
add_subdirectory(ImGui)
add_subdirectory(Platform)
add_subdirectory(Renderer)
add_subdirectory(Utils)

target_include_directories(toodee PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../vendor/glm>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../vendor>
    )

target_compile_definitions(toodee PUBLIC
    GLFW_INCLUDE_NONE
    )

target_link_libraries(toodee PUBLIC
    toodee::imgui
    toodee::glfw3
    toodee::glad
    toodee::stb_image
    spdlog::spdlog
    "-framework OpenAL"
    "-framework OpenGL"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreFoundation"
    )
