set(SOURCES
    stb_image.cpp
    )

add_library(stb_image STATIC
    ${SOURCES}
    )
add_library(toodee::stb_image ALIAS stb_image)

target_include_directories(stb_image PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    )
