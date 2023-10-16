#include "hzpvrpch.hpp"
#include "Platform/OpenGL/OpenGLTexture.hpp"

#include <glad/glad.h>
#include <stb_image.hpp>

namespace HazelPVR
{

    OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
        : m_Path(path)
    {}

    OpenGLTexture2D::~OpenGLTexture2D() {}

    void OpenGLTexture2D::Bind() const {}

} // namespace HazelPVR