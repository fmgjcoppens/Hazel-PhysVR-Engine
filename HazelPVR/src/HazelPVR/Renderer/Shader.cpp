#include "hzpvrpch.hpp"

#include "HazelPVR/Renderer/Shader.hpp"

#include "HazelPVR/Renderer/Renderer.hpp"
#include "Platform/OpenGL/OpenGLShader.hpp"

namespace HazelPVR
{
    Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            HZPVR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        case RendererAPI::API::OpenGL:
            return new OpenGLShader(vertexSrc, fragmentSrc);
        }

        HZPVR_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
} // namespace HazelPVR
