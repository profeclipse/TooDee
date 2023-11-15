#include "TooDee/Renderer/Renderer.h"
#include "TooDee/Renderer/Buffer.h"
#include "TooDee/Platform/OpenGL/OpenGLBuffer.h"

namespace TooDee
{
    Ref<VertexBuffer> VertexBuffer::Create(float* vertices,uint32_t size)
    {
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
                TD_CORE_ASSERT(false,"RendererAPI::None is currently not supported!");
                return nullptr;
			case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLVertexBuffer>(vertices,size);
		}

		TD_CORE_ASSERT(false,"Unknown RendererAPI!");
		return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices,uint32_t count)
    {
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
                TD_CORE_ASSERT(false,"RendererAPI::None is currently not supported!");
                return nullptr;
			case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLIndexBuffer>(indices,count);
		}

		TD_CORE_ASSERT(false,"Unknown RendererAPI!");
		return nullptr;
    }
}
