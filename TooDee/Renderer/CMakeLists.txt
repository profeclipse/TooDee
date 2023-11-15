target_sources(toodee PRIVATE
    Buffer.cpp
    GraphicsContext.cpp
    OrthographicCamera.cpp
    RendererAPI.cpp
    Renderer.cpp
    Shader.cpp
    )

target_sources(toodee PUBLIC
    FILE_SET HEADERS
    FILES
    Buffer.h
    Camera.h
    GraphicsContext.h
    OrthographicCamera.h
    RendererAPI.h
    Renderer.h
    Shader.h
    )
