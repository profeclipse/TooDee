target_sources(toodee PRIVATE
    OpenGLBuffer.cpp
    OpenGLContext.cpp
    OpenGLRendererAPI.cpp
    OpenGLShader.cpp
    OpenGLVertexArray.cpp
    )

target_sources(toodee PUBLIC
    FILE_SET HEADERS
    FILES
    OpenGLBuffer.h
    OpenGLContext.h
    OpenGLRendererAPI.h
    OpenGLShader.h
    OpenGLVertexArray.h
    )
