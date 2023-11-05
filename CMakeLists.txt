cmake_minimum_required(VERSION 3.27.6)

project(toodee
    VERSION 1.0.0
    LANGUAGES CXX C
    )

# Set a default build type if none was specified
set(default_build_type "Release")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
        STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

message(STATUS "Build Type: '${CMAKE_BUILD_TYPE}'.")

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(
    $<$<CONFIG:Debug>:TD_DEBUG>
    )

# External Dependencies

include(FetchContent)

FetchContent_Declare(spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.12.0
    )

FetchContent_MakeAvailable(spdlog)

# ---------------------

option(TOODEE_BUILD_SANDBOX "Build sandbox application" ON)

add_subdirectory(vendor)
add_subdirectory(TooDee)

if(TOODEE_BUILD_SANDBOX)
    add_subdirectory(Sandbox)
endif()
