#include "hzpvrpch.hpp"

#include "HazelPVR/Renderer/Renderer.hpp"
#include "Platform/OpenGL/OpenGLVertexArray.hpp"

namespace HazelPVR
{
    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            HZPVR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        case RendererAPI::API::OpenGL:
            return new OpenGLVertexArray;
        }

        HZPVR_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
} // namespace HazelPVR
