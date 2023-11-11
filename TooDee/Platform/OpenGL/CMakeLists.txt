target_sources(toodee PRIVATE
    OpenGLContext.cpp
    OpenGLRendererAPI.cpp
    OpenGLShader.cpp
    )

target_sources(toodee PUBLIC
    FILE_SET HEADERS
    FILES
    OpenGLContext.h
    OpenGLRendererAPI.h
    OpenGLShader.h
    )
