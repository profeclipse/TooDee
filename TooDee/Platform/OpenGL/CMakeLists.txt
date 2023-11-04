target_sources(toodee PRIVATE
    OpenGLContext.cpp
    OpenGLRendererAPI.cpp
    )

target_sources(toodee PUBLIC
    FILE_SET HEADERS
    FILES
    OpenGLContext.h
    OpenGLRendererAPI.h
    )
