add_library(toodee STATIC)
add_library(toodee::toodee ALIAS toodee)

#file(GLOB_RECURSE sources "*.cpp")

#target_sources(toodee PRIVATE
#    ${sources}
#    )

#file(GLOB_RECURSE headers "*.h")

#target_sources(toodee PUBLIC
#    FILE_SET HEADERS
#    FILES
#    ${headers}
#    )

target_sources(toodee PUBLIC
    FILE_SET HEADERS
    FILES
    TooDee.h
    )

add_subdirectory(Core)
add_subdirectory(Events)
add_subdirectory(Platform)
add_subdirectory(Renderer)

target_include_directories(toodee PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../vendor/glm>
    )

target_compile_definitions(toodee PUBLIC
    GLFW_INCLUDE_NONE
    TD_ENABLE_ASSERTS
    )

target_link_libraries(toodee PUBLIC
    toodee::glad
    toodee::glfw3
    spdlog::spdlog
    "-framework OpenAL"
    "-framework OpenGL"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreFoundation"
    )

