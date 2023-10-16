#include "hzpvrpch.hpp"
#include "HazelPVR/Renderer/Texture.hpp"

#include "HazelPVR/Renderer/Renderer.hpp"
#include "Platform/OpenGL/OpenGLTexture.hpp"

namespace HazelPVR
{

    Ref<Texture2D> Texture2D::Create(const std::string& path)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            HZPVR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLTexture2D>(path);
        }

        HZPVR_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
} // namespace HazelPVR