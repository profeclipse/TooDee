target_sources(toodee PRIVATE
    Application.cpp
    Log.cpp
    Window.cpp
    )

target_sources(toodee PUBLIC
    FILE_SET HEADERS
    FILES
    Application.h
    Assert.h
    Base.h
    EntryPoint.h
    Input.h
    KeyCodes.h
    Log.h
    MouseCodes.h
    PlatformDetection.h
    Window.h
    )
