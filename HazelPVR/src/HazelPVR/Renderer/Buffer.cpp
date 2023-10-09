#include "hzpvrpch.hpp"

#include "HazelPVR/Renderer/Buffer.hpp"
#include "HazelPVR/Renderer/Renderer.hpp"

#include "Platform/OpenGL/OpenGLBuffer.hpp"

namespace HazelPVR
{
    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:     HZPVR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            case RendererAPI::API::OpenGL:   return new OpenGLVertexBuffer(vertices, size);
        }

        HZPVR_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:     HZPVR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            case RendererAPI::API::OpenGL:   return new OpenGLIndexBuffer(indices, size);
        }

        HZPVR_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
} 
