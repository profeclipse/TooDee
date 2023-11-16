#include "TooDee/Platform/OpenGL/OpenGLVertexArray.h"

#include <glad/glad.h>

namespace TooDee
{
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4:
                return GL_FLOAT;
            case ShaderDataType::Mat3:
            case ShaderDataType::Mat4:
                return GL_FLOAT;
            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:
                return GL_INT;
            case ShaderDataType::Bool:
                return GL_BOOL;
            case ShaderDataType::None:
                return 0;
        }

        TD_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glGenVertexArrays(1,&m_rendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1,&m_rendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_rendererID);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
    {
        TD_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(),
                "Vertex Buffer has no layout!");

        glBindVertexArray(m_rendererID);
        vertexBuffer->Bind();

        const auto& layout = vertexBuffer->GetLayout();
        for (const auto& element : layout)
        {
            switch (element.type)
            {
                case ShaderDataType::Float:
                case ShaderDataType::Float2:
                case ShaderDataType::Float3:
                case ShaderDataType::Float4:
                    {
                        glEnableVertexAttribArray(m_vertexBufferIndex);
                        glVertexAttribPointer(m_vertexBufferIndex,
                                element.GetComponentCount(),
                                ShaderDataTypeToOpenGLBaseType(element.type),
                                element.normalized ? GL_TRUE : GL_FALSE,
                                layout.GetStride(),
                                (GLvoid*)element.offset);
                        ++m_vertexBufferIndex;
                    }
                    break;
                case ShaderDataType::Int:
                case ShaderDataType::Int2:
                case ShaderDataType::Int3:
                case ShaderDataType::Int4:
                case ShaderDataType::Bool:
                    {
                        glEnableVertexAttribArray(m_vertexBufferIndex);
                        glVertexAttribIPointer(m_vertexBufferIndex,
                                element.GetComponentCount(),
                                ShaderDataTypeToOpenGLBaseType(element.type),
                                layout.GetStride(),
                                (GLvoid*)element.offset);
                        ++m_vertexBufferIndex;
                    }
                    break;
                case ShaderDataType::Mat3:
                case ShaderDataType::Mat4:
                    {
                        uint8_t count = element.GetComponentCount();
                        for (uint8_t i=0 ; i<count ; ++i)
                        {
                            glEnableVertexAttribArray(m_vertexBufferIndex);
                            glVertexAttribPointer(m_vertexBufferIndex,
                                    count,
                                    ShaderDataTypeToOpenGLBaseType(element.type),
                                    element.normalized ? GL_TRUE : GL_FALSE,
                                    layout.GetStride(),
                                    (GLvoid*)(element.offset + sizeof(float) * count * i));
                            glVertexAttribDivisor(m_vertexBufferIndex,1);
                            ++m_vertexBufferIndex;
                        }
                    }
                    break;
                default:
                    TD_CORE_ASSERT(false,"Unknown ShaderDataType!");
                    break;
            }
        }

        m_vertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_rendererID);
        indexBuffer->Bind();

        m_indexBuffer = indexBuffer;
    }
}
