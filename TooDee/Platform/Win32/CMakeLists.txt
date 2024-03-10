target_sources(toodee PRIVATE
    Win32Input.cpp
    Win32Window.cpp
    Win32PlatformUtils.cpp
    )

target_sources(toodee PUBLIC
    FILE_SET HEADERS
    FILES
    Win32Window.h
    )
