target_sources(toodee PRIVATE
    Buffer.cpp
    GraphicsContext.cpp
    OrthographicCamera.cpp
    RenderCommand.cpp
    RendererAPI.cpp
    Renderer.cpp
    Shader.cpp
    Texture.cpp
    VertexArray.cpp
    )

target_sources(toodee PUBLIC
    FILE_SET HEADERS
    FILES
    Buffer.h
    Camera.h
    GraphicsContext.h
    OrthographicCamera.h
    RenderCommand.h
    RendererAPI.h
    Renderer.h
    Shader.h
    Texture.h
    VertexArray.h
    )
