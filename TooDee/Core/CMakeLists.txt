target_sources(toodee PRIVATE
    Application.cpp
    Layer.cpp
    LayerStack.cpp
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
    Layer.h
    LayerStack.h
    Log.h
    MouseCodes.h
    PlatformDetection.h
    Window.h
    Timer.h
    TimeStep.h
    )
