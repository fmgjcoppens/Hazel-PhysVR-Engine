#include "hzpvrpch.hpp"

#include "HazelPVR/Renderer/Shader.hpp"
#include "Platform/OpenGL/OpenGLShader.hpp"

#include "HazelPVR/Renderer/Renderer.hpp"

namespace HazelPVR
{
    Ref<Shader> Shader::Create(const std::string& filePath)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            HZPVR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLShader>(filePath);
        }

        HZPVR_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            HZPVR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
        }

        HZPVR_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
    {
        HZPVR_CORE_ASSERT(!Exists(name), "Shader already exists in ShaderLibrary!")
        m_Shaders[name] = shader;
    }

    void ShaderLibrary::Add(const Ref<Shader>& shader)
    {
        auto& name = shader->GetName();
        Add(name, shader);
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& filePath)
    {
        auto shader = Shader::Create(filePath);
        Add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filePath)
    {
        auto shader = Shader::Create(filePath);
        Add(name, shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Get(const std::string& name)
    {
        HZPVR_CORE_ASSERT(Exists(name), "Shader not found!")
        return m_Shaders[name];
    }

    bool ShaderLibrary::Exists(const std::string& name) const
    {
        return m_Shaders.find(name) != m_Shaders.end();
    }
} // namespace HazelPVR
