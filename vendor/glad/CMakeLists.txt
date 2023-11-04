set(SOURCES
    src/glad.c
    )

add_library(glad STATIC
    ${SOURCES}
    )
add_library(toodee::glad ALIAS glad)

target_include_directories(glad PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )
