#include "hzpvrpch.h"
#include "Renderer/VertexArray.h"

#include "Renderer/Renderer.h"
#include "OpenGL/OpenGLVertexArray.h"


namespace HazelPVR
{
    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None:     HZPVR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            case RendererAPI::OpenGL:   return new OpenGLVertexArray;
        }

        HZPVR_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
} 
