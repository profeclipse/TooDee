#include "TooDee/Platform/OpenGL/OpenGLBuffer.h"

#include <glad/glad.h>

namespace TooDee
{
    //----------------------------------------------------------------------------
    // VertexBuffer
    //----------------------------------------------------------------------------

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices,uint32_t size)
    {
        glGenBuffers(1,&m_rendererID);
        glBindBuffer(GL_ARRAY_BUFFER,m_rendererID);
        glBufferData(GL_ARRAY_BUFFER,size,vertices,GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1,&m_rendererID);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER,m_rendererID);
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER,0);
    }

    //----------------------------------------------------------------------------
    // InexBuffer
    //----------------------------------------------------------------------------

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices,uint32_t count)
        : m_count(count)
    {
        glGenBuffers(1,&m_rendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_rendererID);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER,count*sizeof(uint32_t),indices,GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1,&m_rendererID);
    }

    void OpenGLIndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_rendererID);
    }

    void OpenGLIndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    }
}
