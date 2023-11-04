target_sources(toodee PRIVATE
    MacOSInput.cpp
    MacOSWindow.cpp
    )

target_sources(toodee PUBLIC
    FILE_SET HEADERS
    FILES
    MacOSWindow.h
    )
