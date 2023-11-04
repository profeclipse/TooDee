target_sources(toodee PRIVATE
    GraphicsContext.cpp
    OrthographicCamera.cpp
    RendererAPI.cpp
    )

target_sources(toodee PUBLIC
    FILE_SET HEADERS
    FILES
    Camera.h
    GraphicsContext.h
    OrthographicCamera.h
    RendererAPI.h
    )
